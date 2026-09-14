#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

// Disable RTOS dependencies (Bare-metal mode)
#define NO_SYS 0

// Enable DHCP
#define LWIP_DHCP 1
#define LWIP_UDP 1
#define LWIP_TCP 1
#define LWIP_ICMP 1

// Basic memory settings (can be tuned later)
#define MEM_ALIGNMENT 4
#define MEM_SIZE (10 * 1024)

#endif /* __LWIPOPTS_H__ */
