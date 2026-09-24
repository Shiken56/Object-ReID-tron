#include "app_camera_ethernet_test.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/pbuf.h"
#include <string.h>

#undef _B
#include <tk/tkernel.h>

/* ========================================== */
/* CHANGE THIS TO YOUR LAPTOP'S ETHERNET IP   */
/* ========================================== */
#define PC_IP_1 192
#define PC_IP_2 168
#define PC_IP_3 1
#define PC_IP_4 100

#define TARGET_PORT 5000
#define UDP_CHUNK_SIZE 1024

static struct udp_pcb *udp_pcb = NULL;
static ip_addr_t target_ip;
static ID sem_ethernet_ready = 0;

/* Global state for the task */
static uint8_t *g_frame_buffer = NULL;
static uint32_t g_width = 0;
static uint32_t g_height = 0;
static uint8_t  g_bpp = 0;

#pragma pack(push, 1)
typedef struct {
    uint32_t frame_id;
    uint16_t chunk_idx;
    uint16_t total_chunks;
} UdpHeader_t;
#pragma pack(pop)

/* The Dedicated Ethernet Background Task */
static void ethernet_task(INT stacd, void *exinf) {
    static uint32_t frame_counter = 0;
    static uint16_t next_chunk = 0;

    while(1) {
        /* Sleep until the Camera Task triggers us */
        tk_wai_sem(sem_ethernet_ready, 1, TMO_FEVR);

        if (udp_pcb == NULL || g_frame_buffer == NULL) continue;

        frame_counter++;
        static uint16_t next_chunk = 0;
        uint32_t total_bytes = g_width * g_height * g_bpp;
        uint16_t total_chunks = (total_bytes + UDP_CHUNK_SIZE - 1) / UDP_CHUNK_SIZE;

        /* Send EXACTLY 3 chunks per wake-up. 
           The hardware MAC usually has 4 TX descriptors. If we send more than 3, 
           HAL_ETH_Transmit blocks and forces a 79ms RTOS timeout delay! */
        uint16_t chunks_to_send = 3;
        
        for (uint16_t i = 0; i < chunks_to_send; i++) {
            uint32_t offset = next_chunk * UDP_CHUNK_SIZE;
            uint32_t chunk_len = UDP_CHUNK_SIZE;
            if (offset + chunk_len > total_bytes) {
                chunk_len = total_bytes - offset;
            }

            struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, sizeof(UdpHeader_t) + chunk_len, PBUF_RAM);
            if (p != NULL) {
                UdpHeader_t *hdr = (UdpHeader_t *)p->payload;
                hdr->frame_id = frame_counter;
                hdr->chunk_idx = next_chunk;
                hdr->total_chunks = total_chunks;

                memcpy((uint8_t *)p->payload + sizeof(UdpHeader_t), g_frame_buffer + offset, chunk_len);

                udp_sendto(udp_pcb, p, &target_ip, TARGET_PORT);
                pbuf_free(p);
            }

            next_chunk++;
            if (next_chunk >= total_chunks) {
                next_chunk = 0;
                frame_counter++;
                break; /* Frame complete, stop sending for this wake-up */
            }
        }
    }
}

void Ethernet_Streamer_Init(void) {
    if (udp_pcb == NULL) {
        udp_pcb = udp_new();
        IP4_ADDR(&target_ip, PC_IP_1, PC_IP_2, PC_IP_3, PC_IP_4);
        udp_bind(udp_pcb, IP_ADDR_ANY, 0);

        /* Create TRON Semaphore for Triggering */
        T_CSEM csem = {.exinf = NULL, .sematr = TA_TFIFO, .isemcnt = 0, .maxsem = 1};
        sem_ethernet_ready = tk_cre_sem(&csem);

        /* Create and Start the Dedicated Ethernet Task */
        T_CTSK ctsk = {
            .exinf = NULL,
            .tskatr = TA_HLNG | TA_RNG3,
            .task = ethernet_task,
            .itskpri = 10,  /* Normal Priority */
            .stksz = 2048
        };
        ID eth_tsk = tk_cre_tsk(&ctsk);
        tk_sta_tsk(eth_tsk, 0);
    }
}

void Ethernet_Streamer_SendFrame(uint8_t *frame_buffer, uint32_t width, uint32_t height, uint8_t bytes_per_pixel) {
    static uint32_t throttle = 0;
    
    /* Trigger Ethernet task EVERY frame (270 FPS triggers). 
       Since we only send 3 chunks per trigger, this yields a solid 5.5 FPS video feed 
       without EVER blocking the MAC descriptors! */

    /* Update the pointers for the ethernet task */
    g_frame_buffer = frame_buffer;
    g_width = width;
    g_height = height;
    g_bpp = bytes_per_pixel;

    /* Trigger the Ethernet Task instantly! */
    if (sem_ethernet_ready > 0) {
        tk_sig_sem(sem_ethernet_ready, 1);
    }
}
