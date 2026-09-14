#include "lwip/sys.h"
#include "lwip/err.h"
#include <tk/tkernel.h>

/* LwIP calls this right as it boots up. */
void sys_init(void) {
    /* µT-Kernel is already running, so no extra initialization is needed here */
}

/* LwIP needs to know the current time in milliseconds for TCP timeouts */
u32_t sys_now(void) {
    SYSTIM systim;
    tk_get_tim(&systim);
    /* systim in TRON is a 64-bit millisecond counter. Cast to 32-bit for LwIP */
    return (u32_t)systim.lo;
}
/* Mask interrupts and return the previous state */
sys_prot_t sys_arch_protect(void) {
    UINT imask;
    DI(imask); /* TRON API: Disable Interrupts */
    return imask;
}

/* Restore the previous interrupt state */
void sys_arch_unprotect(sys_prot_t pval) {
    EI(pval); /* TRON API: Enable Interrupts */
}
