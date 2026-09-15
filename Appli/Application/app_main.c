#include <tk/tkernel.h>
#include <tm/tmonitor.h>

/* LwIP Includes */
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "netif/ethernet.h"

/* MAC driver init function, usually in ethernetif.c */
extern err_t ethernetif_init(struct netif *netif);

struct netif gnetif;

LOCAL void net_task(INT stacd, void *exinf); // task execution function
LOCAL ID	tskid_net;			             // Task ID number
LOCAL T_CTSK ctsk_net = {				     // Task creation information
	.itskpri	= 10,
	.stksz		= 4096,
	.task		= net_task,
	.tskatr		= TA_HLNG | TA_RNG3,
};

LOCAL void net_task(INT stacd, void *exinf)
{
    ip4_addr_t ipaddr;
    ip4_addr_t netmask;
    ip4_addr_t gw;

    /* 1. Start the TCP/IP thread */
    tcpip_init(NULL, NULL);

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

    while (1)
    {
        /* Network background tasks handle ping natively. Delay to yield. */
        tk_dly_tsk(1000); 
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
