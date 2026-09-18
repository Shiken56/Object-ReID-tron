#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#define PRINT(fmt, ...) tm_printf((const UB *)(fmt), ##__VA_ARGS__)

/* LwIP Includes */
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "lwip/udp.h"
#include "netif/ethernet.h"
#include "ethernetif.h"
#include <stdio.h>
#include <string.h>

struct netif gnetif;

LOCAL void net_task(INT stacd, void *exinf); // task execution function
LOCAL ID	tskid_net;			             // Task ID number
LOCAL T_CTSK ctsk_net = {				     // Task creation information
	.itskpri	= 10,
	.stksz		= 4096,
	.task		= net_task,
	.tskatr		= TA_HLNG | TA_RNG0,
};

static void send_raw_broadcast(uint32_t seq)
{
    uint8_t frame[64];
    memset(frame, 0, sizeof(frame));

    /* Destination MAC: FF:FF:FF:FF:FF:FF (Broadcast) */
    memset(&frame[0], 0xFF, 6);

    /* Source MAC: 00:80:E1:00:00:00 */
    frame[6]  = 0x00;
    frame[7]  = 0x80;
    frame[8]  = 0xE1;
    frame[9]  = 0x00;
    frame[10] = 0x00;
    frame[11] = 0x00;

    /* EtherType: 0x88B5 (IEEE 802 Local Experimental) */
    frame[12] = 0x88;
    frame[13] = 0xB5;

    /* Payload */
    snprintf((char *)&frame[14], sizeof(frame) - 14, "STM32N6 Beacon #%lu", (unsigned long)seq);

    ethernetif_send_raw(frame, 60);
}

LOCAL void net_task(INT stacd, void *exinf)
{
    ip4_addr_t ipaddr;
    ip4_addr_t netmask;
    ip4_addr_t gw;
    struct udp_pcb *upcb = NULL;
    uint32_t tx_timer = 0;
    uint32_t pkt_seq = 0;
    uint32_t last_rx_count = 0;
    uint32_t last_tx_count = 0;

    PRINT("\r\n========================================\r\n");
    PRINT("  STM32N657 Ethernet TX & Ping Test    \r\n");
    PRINT("========================================\r\n");

    /* 1. Start the TCP/IP thread */
    PRINT("[NET] Starting TCP/IP thread...\r\n");
    tcpip_init(NULL, NULL);
    PRINT("[NET] TCP/IP thread running.\r\n");

    /* 2. Configure Static IP Address: 192.168.1.10 */
    IP4_ADDR(&ipaddr, 192, 168, 1, 10);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
    IP4_ADDR(&gw, 192, 168, 1, 1);

    /* 3. Add the network interface */
    netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

    /* 4. Set as default, bring up the interface and link */
    netif_set_default(&gnetif);
    netif_set_up(&gnetif);
    netif_set_link_up(&gnetif);

    PRINT("[NET] Interface is UP!\r\n");
    PRINT("[NET] Static IP  : 192.168.1.10\r\n");
    PRINT("[NET] Netmask    : 255.255.255.0\r\n");
    PRINT("[NET] Gateway    : 192.168.1.1\r\n");
    PRINT("[NET] Broadcasting test frames every 1s (check Wireshark!)\r\n");

    /* Create UDP PCB for UDP broadcast */
    upcb = udp_new();

    while (1)
    {
        /* Poll Ethernet driver for incoming packets (ARP, ICMP ping, etc.) */
        ethernetif_input(&gnetif);

        /* Send broadcast test packet every ~1 second (500 * 2ms) */
        if (++tx_timer >= 500) {
            tx_timer = 0;
            pkt_seq++;

            /* 1. Transmit raw Ethernet broadcast frame */
            send_raw_broadcast(pkt_seq);

            /* 2. Transmit UDP broadcast packet to 255.255.255.255:12345 */
            if (upcb != NULL) {
                struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, 64, PBUF_RAM);
                if (p != NULL) {
                    int len = snprintf((char *)p->payload, 64, "STM32N6 UDP Broadcast #%lu\r\n", (unsigned long)pkt_seq);
                    p->len = (u16_t)len;
                    p->tot_len = (u16_t)len;
                    udp_sendto(upcb, p, IP_ADDR_BROADCAST, 12345);
                    pbuf_free(p);
                }
            }
        }

        /* Print activity whenever packets are received or transmitted */
        if (g_rx_pkt_count != last_rx_count || g_tx_pkt_count != last_tx_count) {
            PRINT("[NET ACTIVITY] RX Total: %lu | TX Total: %lu\r\n",
                  (unsigned long)g_rx_pkt_count, (unsigned long)g_tx_pkt_count);
            last_rx_count = g_rx_pkt_count;
            last_tx_count = g_tx_pkt_count;
        }

        tk_dly_tsk(2);
    }
}

EXPORT INT usermain(void)
{
	/* Create & Start Network Task */
	tskid_net = tk_cre_tsk(&ctsk_net);
	tk_sta_tsk(tskid_net, 0);

	tk_slp_tsk(TMO_FEVR);

	return 0;
}
