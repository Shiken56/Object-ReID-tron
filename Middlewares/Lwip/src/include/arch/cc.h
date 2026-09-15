#ifndef __ARCH_CC_H__
#define __ARCH_CC_H__

#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

/* Define ARM Cortex-M hardware endianness */
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif

/* GCC struct packing macros required by LwIP */
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_STRUCT __attribute__ ((__packed__))
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x

/* Empty diagnostic macros to prevent compiler warnings for now */
#define LWIP_PLATFORM_DIAG(x)   do { } while(0)
#define LWIP_PLATFORM_ASSERT(x) do { } while(0)

/* Random number generation for network security/ports */
#define LWIP_RAND() ((uint32_t)rand())

#endif /* __ARCH_CC_H__ */
