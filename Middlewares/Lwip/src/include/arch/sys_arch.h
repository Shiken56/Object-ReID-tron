#ifndef __SYS_ARCH_H__
#define __SYS_ARCH_H__

/* Prevent GCC macro collision with TRON typedefs */
#undef _B
#include <tk/tkernel.h>

/* µT-Kernel uses IDs (integers) for OS objects */
typedef ID sys_sem_t;
typedef ID sys_mutex_t;
typedef ID sys_mbox_t;
typedef ID sys_thread_t;

/* Lightweight protection type (stores interrupt state) */
typedef UINT sys_prot_t;

/* Define what an invalid/empty object looks like */
#define SYS_MBOX_NULL (0)
#define SYS_SEM_NULL  (0)

#endif /* __SYS_ARCH_H__ */
