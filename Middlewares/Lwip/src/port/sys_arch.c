#include "lwip/sys.h"
#include "lwip/err.h"
#include <tk/tkernel.h>

/* ========================================================================= */
/* SYSTEM INITIALIZATION & TIME                                              */
/* ========================================================================= */

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

/* ========================================================================= */
/* CRITICAL SECTION PROTECTION                                               */
/* ========================================================================= */

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

/* Create a new semaphore */
err_t sys_sem_new(sys_sem_t *sem, u8_t count) {
    T_CSEM csem = {0};
    csem.sematr  = TA_TFIFO;      /* Tasks wait in FIFO order */
    csem.isemcnt = count;         /* Initial semaphore count */
    csem.maxsem  = 255;           /* Maximum allowed count */

    *sem = tk_cre_sem(&csem);     /* Call TRON API */

    if (*sem <= 0) {
        return ERR_MEM;           /* Return LwIP memory error if creation fails */
    }
    return ERR_OK;
}

/* Signal (release) a semaphore */
void sys_sem_signal(sys_sem_t *sem) {
    tk_sig_sem(*sem, 1); /* Signal the semaphore by 1 */
}

/* Wait (acquire) a semaphore */
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout) {
    TMO tmout = (timeout == 0) ? TMO_FEVR : (TMO)timeout;
    u32_t start_time = sys_now(); /* Record start time */

    ER err = tk_wai_sem(*sem, 1, tmout); /* Wait for the semaphore */

    if (err == E_TMOUT) {
        return SYS_ARCH_TIMEOUT; /* TRON timed out */
    }

    /* Return the elapsed time in milliseconds */
    return (sys_now() - start_time);
}

/* Delete a semaphore */
void sys_sem_free(sys_sem_t *sem) {
    tk_del_sem(*sem);
    *sem = SYS_SEM_NULL; /* Clear the ID for safety */
}

/* Create a new mailbox (Message Buffer) */
err_t sys_mbox_new(sys_mbox_t *mbox, int size) {
    T_CMBF cmbf = {0};

    /* If LwIP asks for a size of 0, give it a default robust size */
    if (size == 0) {
        size = 64;
    }

    cmbf.mbfatr = TA_TFIFO;                 /* Tasks wait in FIFO order */
    cmbf.bufsz  = size * sizeof(void *);    /* Total buffer size */
    cmbf.maxmsz = sizeof(void *);           /* We are only sending memory pointers */

    *mbox = tk_cre_mbf(&cmbf);

    if (*mbox <= 0) {
        return ERR_MEM;
    }
    return ERR_OK;
}

/* Delete a mailbox */
void sys_mbox_free(sys_mbox_t *mbox) {
    tk_del_mbf(*mbox);
    *mbox = SYS_MBOX_NULL;
}

/* Post a message to the mailbox (Blocking) */
void sys_mbox_post(sys_mbox_t *mbox, void *msg) {
    tk_snd_mbf(*mbox, &msg, sizeof(void *), TMO_FEVR);
}

/* Try to post a message (Non-Blocking) */
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg) {
    /* TMO_POL tells TRON to poll/return instantly if the buffer is full */
    ER err = tk_snd_mbf(*mbox, &msg, sizeof(void *), TMO_POL);

    if (err == E_TMOUT || err == E_OACV) {
        return ERR_MEM;
    }
    return ERR_OK;
}

/* Wait for and fetch a message from the mailbox */
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout) {
    TMO tmout = (timeout == 0) ? TMO_FEVR : (TMO)timeout;
    u32_t start_time = sys_now();
    void *dummy;

    /* LwIP occasionally passes NULL if it just wants to wait, not read */
    if (msg == NULL) {
        msg = &dummy;
    }

    ER err = tk_rcv_mbf(*mbox, msg, tmout);
    if (err == E_TMOUT) {
        return SYS_ARCH_TIMEOUT;
    }

    return (sys_now() - start_time);
}

/* Try to fetch a message instantly */
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg) {
    void *dummy;
    if (msg == NULL) {
        msg = &dummy;
    }

    ER err = tk_rcv_mbf(*mbox, msg, TMO_POL);
    if (err == E_TMOUT) {
        return SYS_MBOX_EMPTY;
    }

    return 0; /* 0 milliseconds elapsed */
}

/* Create and start a new thread (TRON Task) */
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio) {
    T_CTSK ctsk = {0};
    ID tskid;

    /* 1. Configure the TRON task attributes */
    ctsk.tskatr  = TA_HLNG;       /* Indicates a high-level language (C) program */
    ctsk.task    = (FP)thread;    /* Function pointer to LwIP's thread routine */
    ctsk.itskpri = prio;          /* Task priority passed from LwIP */
    ctsk.stksz   = stacksize;     /* Stack size allocated for this thread */

    /* 2. Create the task in µT-Kernel */
    tskid = tk_cre_tsk(&ctsk);

    if (tskid <= 0) {
        /* Task creation failed (e.g., out of memory or invalid priority) */
        return 0;
    }

    /* 3. Start the task, passing LwIP's required argument (msg/ptr) */
    tk_sta_tsk(tskid, (INT)arg);

    return tskid;
}
