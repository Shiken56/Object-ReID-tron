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


/* 3. Standard IPv4 UDP Broadcast on Port 5000 (EtherType 0x0800) */
static void send_raw_udp_broadcast(uint32_t seq)
{
    uint8_t frame[64];
    memset(frame, 0, sizeof(frame));

    /* Ethernet Header (14 bytes) */
    memset(&frame[0], 0xFF, 6);
    frame[6] = 0x00; frame[7] = 0x80; frame[8] = 0xE1;
    frame[9] = 0x00; frame[10] = 0x00; frame[11] = 0x00;
    frame[12] = 0x08; frame[13] = 0x00;                 /* EtherType: IPv4 */

    /* IPv4 Header (20 bytes) */
    frame[14] = 0x45;
    uint16_t total_len = 20 + 8 + 18;                   /* IP(20) + UDP(8) + Payload(18) = 46 */
    frame[16] = (total_len >> 8) & 0xFF;
    frame[17] = total_len & 0xFF;
    frame[18] = (seq >> 8) & 0xFF; frame[19] = seq & 0xFF;
    frame[22] = 64;                                     /* TTL */
    frame[23] = 17;                                     /* Protocol: UDP */
    frame[26] = 192; frame[27] = 168; frame[28] = 1; frame[29] = 10;   /* Src IP: 192.168.1.10 */
    frame[30] = 255; frame[31] = 255; frame[32] = 255; frame[33] = 255; /* Dst IP: 255.255.255.255 */

    /* Checksum */
    uint32_t sum = 0;
    for (int i = 14; i < 34; i += 2) {
        sum += ((uint16_t)frame[i] << 8) | frame[i + 1];
    }
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    uint16_t ip_chk = ~sum;
    frame[24] = (ip_chk >> 8) & 0xFF; frame[25] = ip_chk & 0xFF;

    /* UDP Header (8 bytes) */
    frame[34] = (5000 >> 8) & 0xFF; frame[35] = 5000 & 0xFF; /* Src Port: 5000 */
    frame[36] = (5000 >> 8) & 0xFF; frame[37] = 5000 & 0xFF; /* Dst Port: 5000 */
    uint16_t udp_len = 8 + 18;
    frame[38] = (udp_len >> 8) & 0xFF; frame[39] = udp_len & 0xFF;

    /* Payload */
    snprintf((char *)&frame[42], sizeof(frame) - 42, "STM32N6 #%lu", (unsigned long)seq);

    ethernetif_send_raw(frame, 14 + total_len);
}

LOCAL void net_task(INT stacd, void *exinf)
{
    ip4_addr_t ipaddr;
    ip4_addr_t netmask;
    ip4_addr_t gw;
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

    uint32_t heartbeat_timer = 0;
    uint32_t heartbeat_sec = 0;

    while (1)
    {
        /* 1. Poll Ethernet driver for incoming packets (ARP, ICMP ping, etc.) */
        ethernetif_input(&gnetif);

        /* 2. Every ~1 second (500 * 2ms): Check link/speed & send beacon */
        if (++tx_timer >= 500) {
            tx_timer = 0;
            pkt_seq++;

            /* Dynamic link status & speed detection (1000M vs 100M auto-switch) */
            ethernetif_check_link_and_speed(&gnetif);

            /* Send standard IPv4 UDP broadcast on port 5000 (EtherType 0x0800) */
            send_raw_udp_broadcast(pkt_seq);
        }

        /* 3. Every ~3 seconds (1500 * 2ms): Network health heartbeat */
        if (++heartbeat_timer >= 1500) {
            heartbeat_timer = 0;
            heartbeat_sec += 3;

            PRINT("[HEARTBEAT %lus] Total RX: %lu pkts | Total TX: %lu pkts | Link: %s\r\n",
                  (unsigned long)heartbeat_sec,
                  (unsigned long)g_rx_pkt_count,
                  (unsigned long)g_tx_pkt_count,
                  netif_is_link_up(&gnetif) ? "LINK UP" : "LINK DOWN");
        }

        /* microT-Kernel OS delay: yields CPU to TCP/IP thread and idle tasks */
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
