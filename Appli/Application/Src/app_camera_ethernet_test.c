#include "app_camera_ethernet_test.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/pbuf.h"
#include <string.h>

/* ========================================== */
/* CHANGE THIS TO YOUR LAPTOP'S ETHERNET IP   */
/* ========================================== */
#define PC_IP_1 169
#define PC_IP_2 254
#define PC_IP_3 81
#define PC_IP_4 194

#define TARGET_PORT 5000
#define UDP_CHUNK_SIZE 1024

static struct udp_pcb *udp_pcb = NULL;
static ip_addr_t target_ip;

#pragma pack(push, 1)
typedef struct {
    uint32_t frame_id;
    uint16_t chunk_idx;
    uint16_t total_chunks;
} UdpHeader_t;
#pragma pack(pop)

void Ethernet_Streamer_Init(void) {
    if (udp_pcb == NULL) {
        udp_pcb = udp_new();
        IP4_ADDR(&target_ip, PC_IP_1, PC_IP_2, PC_IP_3, PC_IP_4);
        udp_bind(udp_pcb, IP_ADDR_ANY, 0);
    }
}

void Ethernet_Streamer_SendFrame(uint8_t *frame_buffer, uint32_t width, uint32_t height) {
    static uint32_t frame_counter = 0;
    static uint32_t throttle = 0;
    
    if (udp_pcb == NULL) return;

    /* Throttle to ~30 fps. Camera runs at ~270 FPS, so we send every 9th frame. 
       This prevents Ethernet from becoming congested. */
    throttle++;
    if (throttle % 9 != 0) return;

    frame_counter++;
    uint32_t total_bytes = width * height * 3; // Assuming RGB888
    uint16_t total_chunks = (total_bytes + UDP_CHUNK_SIZE - 1) / UDP_CHUNK_SIZE;

    uint32_t offset = 0;
    for (uint16_t i = 0; i < total_chunks; i++) {
        uint32_t chunk_len = UDP_CHUNK_SIZE;
        if (offset + chunk_len > total_bytes) {
            chunk_len = total_bytes - offset;
        }

        struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, sizeof(UdpHeader_t) + chunk_len, PBUF_RAM);
        if (p != NULL) {
            UdpHeader_t *hdr = (UdpHeader_t *)p->payload;
            hdr->frame_id = frame_counter;
            hdr->chunk_idx = i;
            hdr->total_chunks = total_chunks;

            memcpy((uint8_t *)p->payload + sizeof(UdpHeader_t), frame_buffer + offset, chunk_len);

            udp_sendto(udp_pcb, p, &target_ip, TARGET_PORT);
            pbuf_free(p);
        }
        offset += chunk_len;
    }
}
