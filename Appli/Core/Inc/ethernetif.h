#ifndef ETHERNETIF_H
#define ETHERNETIF_H

#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

err_t ethernetif_init(struct netif *netif);
void ethernetif_input(struct netif *netif);
int8_t ethernetif_send_raw(const uint8_t *data, uint16_t len);
void ethernetif_dump_diagnostics(void);
void ethernetif_dump_tx_diagnostics(void);
int ethernetif_check_link_and_speed(struct netif *netif);
void dump_rx_desc_state(const char *moment);

extern volatile uint32_t g_rx_pkt_count;
extern volatile uint32_t g_tx_pkt_count;

#ifdef __cplusplus
}
#endif

#endif /* ETHERNETIF_H */
