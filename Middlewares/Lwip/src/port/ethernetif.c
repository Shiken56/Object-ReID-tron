#include "lwip/opt.h"
#include "lwip/netif.h"
#include "lwip/etharp.h"
#include "netif/ethernet.h"
#include "stm32n6xx_hal.h"
#include <string.h>

/* The global ST HAL Ethernet handle defined in main.c */
extern ETH_HandleTypeDef heth1;

#define IFNAME0 's'
#define IFNAME1 't'

/* ========================================================================= */
/* 1. LOW LEVEL OUTPUT (TRANSMIT)                                            */
/* ========================================================================= */
static err_t low_level_output(struct netif *netif, struct pbuf *p) {
    uint32_t i = 0;
    struct pbuf *q;
    err_t errval = ERR_OK;

    ETH_BufferTypeDef Txbuffer[ETH_TX_DESC_CNT];
    memset(Txbuffer, 0, ETH_TX_DESC_CNT * sizeof(ETH_BufferTypeDef));

    for (q = p; q != NULL; q = q->next) {
        if (i >= ETH_TX_DESC_CNT) {
            return ERR_IF;
        }
        Txbuffer[i].buffer = q->payload;
        Txbuffer[i].len    = q->len;
        Txbuffer[i].next   = (q->next == NULL) ? NULL : &Txbuffer[i + 1];
        i++;
    }

    ETH_TxPacketConfig TxConfig = {0};
    TxConfig.Length   = p->tot_len;
    TxConfig.TxBuffer = Txbuffer;

    if (HAL_ETH_Transmit_IT(&heth1, &TxConfig) != HAL_OK) {
        errval = ERR_IF;
    }

    return errval;
}

/* ========================================================================= */
/* 2. LOW LEVEL INPUT (RECEIVE)                                              */
/* ========================================================================= */
static struct pbuf *low_level_input(struct netif *netif) {
    struct pbuf *p = NULL;
    void *appBuff = NULL;

    /* The STM32N6 uses the newer unified ReadData API */
    if (HAL_ETH_ReadData(&heth1, &appBuff) == HAL_OK) {

        /* FIX: Access Queue 0 from the RxDescList array */
        uint32_t framelength = heth1.RxDescList[0].RxDataLength;

        /* Allocate LwIP memory */
        p = pbuf_alloc(PBUF_RAW, framelength, PBUF_POOL);

        if (p != NULL) {
            /* Copy the hardware buffer into the LwIP memory */
            memcpy(p->payload, appBuff, framelength);
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

    HAL_ETH_Start_IT(&heth1);
}

/* ========================================================================= */
/* 4. LWIP STACK FEEDER                                                      */
/* ========================================================================= */
void ethernetif_input(struct netif *netif) {
    struct pbuf *p = low_level_input(netif);

    if (p != NULL) {
        if (netif->input(p, netif) != ERR_OK) {
            pbuf_free(p);
        }
    }
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
