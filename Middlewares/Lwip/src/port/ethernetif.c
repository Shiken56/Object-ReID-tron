#include "lwip/opt.h"
#include "lwip/netif.h"
#include "lwip/etharp.h"
#include "netif/ethernet.h"
#include "ethernetif.h"
#include "stm32n6xx_hal.h"
extern int tm_printf(const void *format, ...);
#include <string.h>

/* The global ST HAL Ethernet handle defined in main.c */
extern ETH_HandleTypeDef heth1;

#define IFNAME0 's'
#define IFNAME1 't'

/* Packet counters for live debugging */
volatile uint32_t g_rx_pkt_count = 0;
volatile uint32_t g_tx_pkt_count = 0;

/* ========================================================================= */
/* RX BUFFER ALLOCATION IN NON-CACHEABLE MEMORY                              */
/* ========================================================================= */
#define ETH_RX_BUFFER_CNT   (ETH_RX_DESC_CNT * 2)
#define ETH_RX_BUFFER_SIZE  1536

static uint8_t RxBuffers[ETH_RX_BUFFER_CNT][ETH_RX_BUFFER_SIZE] __attribute__((section(".noncacheable"), aligned(32)));
static uint32_t rx_alloc_idx = 0;

/**
 * @brief  HAL ETH Rx Allocate Callback.
 *         Supplies DMA descriptor with a buffer address in non-cacheable RAM.
 */
void HAL_ETH_RxAllocateCallback(uint8_t **buff)
{
    *buff = RxBuffers[rx_alloc_idx];
    rx_alloc_idx = (rx_alloc_idx + 1) % ETH_RX_BUFFER_CNT;
}

/**
 * @brief  HAL ETH Rx Link Callback.
 *         Links the received buffer to the application buffer pointer.
 */
void HAL_ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t Length)
{
    (void)Length;
    if (*pStart == NULL) {
        *pStart = buff;
    }
    *pEnd = buff;
}

static uint8_t TxBuffers[ETH_TX_DESC_CNT][1536] __attribute__((section(".noncacheable"), aligned(32)));
static ETH_BufferTypeDef Txbuffer[ETH_TX_DESC_CNT];

/* ========================================================================= */
/* 1. LOW LEVEL OUTPUT (TRANSMIT)                                            */
/* ========================================================================= */
static err_t low_level_output(struct netif *netif, struct pbuf *p) {
    (void)netif;
    if (p == NULL || p->tot_len > 1514) {
        return ERR_BUF;
    }

    /* Copy pbuf chain into non-cacheable DMA-safe TX buffer */
    pbuf_copy_partial(p, TxBuffers[0], p->tot_len, 0);

    Txbuffer[0].buffer = TxBuffers[0];
    Txbuffer[0].len    = p->tot_len;
    Txbuffer[0].next   = NULL;

    ETH_TxPacketConfigTypeDef TxConfig = {0};
    TxConfig.Length     = p->tot_len;
    TxConfig.TxBuffer   = &Txbuffer[0];
    TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;

    if (HAL_ETH_Transmit(&heth1, &TxConfig, 100) != HAL_OK) {
        return ERR_IF;
    }

    g_tx_pkt_count++;
    tm_printf("[ETH TX] Transmitted packet #%u (Length=%u bytes)\n", g_tx_pkt_count, (unsigned)p->tot_len);

    return ERR_OK;
}

/**
 * @brief  Sends a raw Ethernet frame directly via DMA (useful for testing wire connectivity).
 */
int8_t ethernetif_send_raw(const uint8_t *data, uint16_t len) {
    if (data == NULL || len == 0 || len > 1514) {
        return -1;
    }

    memcpy(TxBuffers[0], data, len);

    Txbuffer[0].buffer = TxBuffers[0];
    Txbuffer[0].len    = len;
    Txbuffer[0].next   = NULL;

    ETH_TxPacketConfigTypeDef TxConfig = {0};
    TxConfig.Length     = len;
    TxConfig.TxBuffer   = &Txbuffer[0];
    TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;

    if (HAL_ETH_Transmit(&heth1, &TxConfig, 100) != HAL_OK) {
        return -1;
    }

    g_tx_pkt_count++;
    tm_printf("[ETH TX RAW] Broadcast packet sent #%u (Length=%u bytes)\n", g_tx_pkt_count, (unsigned)len);
    return 0;
}

/* ========================================================================= */
/* 2. LOW LEVEL INPUT (RECEIVE)                                              */
/* ========================================================================= */
static struct pbuf *low_level_input(struct netif *netif) {
    (void)netif;
    struct pbuf *p = NULL;
    void *appBuff = NULL;

    /* The STM32N6 uses the unified ReadData API */
    if (HAL_ETH_ReadData(&heth1, &appBuff) == HAL_OK) {
        uint32_t framelength = heth1.RxDescList[heth1.RxOpCH].RxDataLength;

        if (framelength > 0 && appBuff != NULL) {
            g_rx_pkt_count++;
            tm_printf("[ETH RX] Received packet #%u (Length=%u bytes)\n", g_rx_pkt_count, (unsigned)framelength);

            /* Allocate LwIP memory */
            p = pbuf_alloc(PBUF_RAW, (u16_t)framelength, PBUF_POOL);

            if (p != NULL) {
                /* Copy the hardware buffer into LwIP pbuf (handles chained pbufs safely) */
                pbuf_take(p, appBuff, (u16_t)framelength);
            }
        }
    }

    return p;
}

/* ========================================================================= */
/* 3. LOW LEVEL INITIALIZATION                                               */
/* ========================================================================= */
static void low_level_init(struct netif *netif) {
    netif->hwaddr_len = ETH_HWADDR_LEN;

    netif->hwaddr[0] = heth1.Init.MACAddr[0];
    netif->hwaddr[1] = heth1.Init.MACAddr[1];
    netif->hwaddr[2] = heth1.Init.MACAddr[2];
    netif->hwaddr[3] = heth1.Init.MACAddr[3];
    netif->hwaddr[4] = heth1.Init.MACAddr[4];
    netif->hwaddr[5] = heth1.Init.MACAddr[5];

    netif->mtu = 1500;
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

    /* Probe PHY on MDIO bus and report status */
    for (uint32_t addr = 0; addr <= 3; addr++) {
        uint32_t phy_bmsr = 0;
        if (HAL_ETH_ReadPHYRegister(&heth1, addr, 1, &phy_bmsr) == HAL_OK) {
            if (phy_bmsr != 0 && phy_bmsr != 0xFFFF) {
                tm_printf("[ETH PHY] PHY at addr %u: BMSR=0x%04X (Link %s)\n",
                          addr, (unsigned)phy_bmsr, (phy_bmsr & 0x0004) ? "UP" : "DOWN");
            }
        }
    }

    HAL_ETH_Start(&heth1);
    tm_printf("[ETH] Ethernet DMA started. MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
              netif->hwaddr[0], netif->hwaddr[1], netif->hwaddr[2],
              netif->hwaddr[3], netif->hwaddr[4], netif->hwaddr[5]);
}

/* ========================================================================= */
/* 4. LWIP STACK FEEDER                                                      */
/* ========================================================================= */
void ethernetif_input(struct netif *netif) {
    struct pbuf *p;

    /* Drain all received packets waiting in Ethernet DMA descriptors */
    do {
        p = low_level_input(netif);
        if (p != NULL) {
            if (netif->input(p, netif) != ERR_OK) {
                pbuf_free(p);
            }
        }
    } while (p != NULL);
}

/* ========================================================================= */
/* 5. LWIP INTERFACE INITIALIZATION                                          */
/* ========================================================================= */
err_t ethernetif_init(struct netif *netif) {
    LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
    netif->hostname = "stm32n6_tron";
#endif

    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;

    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

    low_level_init(netif);

    return ERR_OK;
}
