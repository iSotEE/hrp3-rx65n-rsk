/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#if !(TKERNEL_PRID == 0x0006U && (TKERNEL_PRVER & 0xf000U) == 0x3000U)
#error The kernel does not match this configuration file.
#endif

/*
 *  Include Directives
 */

#ifdef TOPPERS_ML_AUTO
#endif
#include "target_timer.h"
#ifdef TOPPERS_SUPPORT_OVRHDR
#endif
#include "cfg_attmod1.h"

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_sstack_TASK1[COUNT_STK_T(DEFAULT_SSTKSZ)] __attribute__((section(".noinit_kernel"),nocommon));
static STK_T _kernel_ustack_TASK1[COUNT_STK_T(4096)] __attribute__((section(".ustack_TASK1"),nocommon));
static STK_T _kernel_sstack_TASK1_0[COUNT_STK_T(DEFAULT_SSTKSZ)] __attribute__((section(".noinit_kernel"),nocommon));
static STK_T _kernel_ustack_TASK1_0[COUNT_STK_T(4096)] __attribute__((section(".ustack_TASK1_0"),nocommon));
static STK_T _kernel_sstack_TASK2[COUNT_STK_T(DEFAULT_SSTKSZ)] __attribute__((section(".noinit_kernel"),nocommon));
static STK_T _kernel_ustack_TASK2[COUNT_STK_T(4096)] __attribute__((section(".ustack_TASK2"),nocommon));
static STK_T _kernel_sstack_TASK2_0[COUNT_STK_T(DEFAULT_SSTKSZ)] __attribute__((section(".noinit_kernel"),nocommon));
static STK_T _kernel_ustack_TASK2_0[COUNT_STK_T(4096)] __attribute__((section(".ustack_TASK2_0"),nocommon));
static STK_T _kernel_sstack_TASK3[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".noinit_kernel"),nocommon));
static STK_T _kernel_sstack_TASK3_0[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".noinit_kernel"),nocommon));
const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (DOM1), (TA_NULL), (intptr_t)(1), (TASK)(task1_1), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(DEFAULT_SSTKSZ), _kernel_sstack_TASK1, ROUND_STK_T(4096), _kernel_ustack_TASK1, { TACP(DOM1), TACP(DOM1), TACP(DOM1), TACP(DOM1) } },
	{ (DOM1), (TA_NULL), (intptr_t)(1), (TASK)(task0_1), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(DEFAULT_SSTKSZ), _kernel_sstack_TASK1_0, ROUND_STK_T(4096), _kernel_ustack_TASK1_0, { TACP(DOM1), TACP(DOM1), TACP(DOM1), TACP(DOM1) } },
	{ (DOM2), (TA_NULL), (intptr_t)(1), (TASK)(task2_1), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(DEFAULT_SSTKSZ), _kernel_sstack_TASK2, ROUND_STK_T(4096), _kernel_ustack_TASK2, { TACP(DOM2), TACP(DOM2), TACP(DOM2), TACP(DOM2) } },
	{ (DOM2), (TA_NULL), (intptr_t)(1), (TASK)(task0_1), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(DEFAULT_SSTKSZ), _kernel_sstack_TASK2_0, ROUND_STK_T(4096), _kernel_ustack_TASK2_0, { TACP(DOM2), TACP(DOM2), TACP(DOM2), TACP(DOM2) } },
	{ (TDOM_KERNEL), (TA_NULL), (intptr_t)(1), (TASK)(task3_1), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_sstack_TASK3, 0, NULL, { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL } },
	{ (TDOM_KERNEL), (TA_NULL), (intptr_t)(1), (TASK)(task0_1), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_sstack_TASK3_0, 0, NULL, { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL } }
};

TCB _kernel_tcb_table[TNUM_TSKID];

const ID _kernel_torder_table[TNUM_TSKID] = { 
	TASK1, TASK1_0, TASK2, TASK2_0, TASK3, TASK3_0
};

STK_T _kernel_ustack_TOPPERS_RAM_DUMMY1[COUNT_STK_T(4096)] __attribute__((section(".ustack_TOPPERS_RAM_DUMMY1"),nocommon));
STK_T _kernel_ustack_TOPPERS_RAM2_DUMMY1[COUNT_STK_T(4096)] __attribute__((section(".ustack_TOPPERS_RAM2_DUMMY1"),nocommon));
/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

TOPPERS_EMPTY_LABEL(const SEMINIB, _kernel_seminib_table);
TOPPERS_EMPTY_LABEL(SEMCB, _kernel_semcb_table);

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

TOPPERS_EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);
TOPPERS_EMPTY_LABEL(FLGCB, _kernel_flgcb_table);

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

TOPPERS_EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);
TOPPERS_EMPTY_LABEL(DTQCB, _kernel_dtqcb_table);

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);
TOPPERS_EMPTY_LABEL(PDQCB, _kernel_pdqcb_table);

/*
 *  Mutex Functions
 */

const ID _kernel_tmax_mtxid = (TMIN_MTXID + TNUM_MTXID - 1);

TOPPERS_EMPTY_LABEL(const MTXINIB, _kernel_mtxinib_table);
TOPPERS_EMPTY_LABEL(MTXCB, _kernel_mtxcb_table);

/*
 *  Message Buffer Functions
 */

const ID _kernel_tmax_mbfid = (TMIN_MBFID + TNUM_MBFID - 1);

TOPPERS_EMPTY_LABEL(const MBFINIB, _kernel_mbfinib_table);
TOPPERS_EMPTY_LABEL(MBFCB, _kernel_mbfcb_table);

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
TOPPERS_EMPTY_LABEL(MPFCB, _kernel_mpfcb_table);

/*
 *  Cyclic Notification Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

TOPPERS_EMPTY_LABEL(const CYCINIB, _kernel_cycinib_table);
TOPPERS_EMPTY_LABEL(CYCCB, _kernel_cyccb_table);

/*
 *  Alarm Notification Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

TOPPERS_EMPTY_LABEL(const ALMINIB, _kernel_alminib_table);
TOPPERS_EMPTY_LABEL(ALMCB, _kernel_almcb_table);

/*
 *  Interrupt Management Functions
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(isrid)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(isrid)
#endif /* LOG_ISR_LEAVE */

#define TNUM_DEF_INHNO	2
const uint_t _kernel_tnum_def_inhno = TNUM_DEF_INHNO;

INTHDR_ENTRY(INHNO_HRT, 0, _kernel_target_hrt_handler)
INTHDR_ENTRY(INHNO_TWDTIMER, 1, _kernel_target_twdtimer_handler)

const INHINIB _kernel_inhinib_table[TNUM_DEF_INHNO] = {
	{ (INHNO_HRT), (TA_NULL), (FP)(INT_ENTRY(INHNO_HRT, _kernel_target_hrt_handler)) },
	{ (INHNO_TWDTIMER), (TA_NULL), (FP)(INT_ENTRY(INHNO_TWDTIMER, _kernel_target_twdtimer_handler)) }
};

#define TNUM_CFG_INTNO	2
const uint_t _kernel_tnum_cfg_intno = TNUM_CFG_INTNO;

const INTINIB _kernel_intinib_table[TNUM_CFG_INTNO] = {
	{ (INTNO_HRT), (TA_ENAINT | INTATR_HRT), (INTPRI_HRT) },
	{ (INTNO_TWDTIMER), (TA_ENAINT|INTATR_TWDTIMER), (INTPRI_TWDTIMER) }
};

/*
 *  CPU Exception Management Functions
 */

#define TNUM_DEF_EXCNO	0
const uint_t _kernel_tnum_def_excno = TNUM_DEF_EXCNO;

TOPPERS_EMPTY_LABEL(const EXCINIB, _kernel_excinib_table);

/*
 *  Extended Service Calls
 */

const FN _kernel_tmax_fncd = TMAX_FNCD;

TOPPERS_EMPTY_LABEL(const SVCINIB, _kernel_svcinib_table);

/*
 *  Access Permission Vector
 */

const ACVCT _kernel_sysstat_acvct = { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL };

/*
 *  Stack Area for Non-task Context
 */

static STK_T _kernel_istack[COUNT_STK_T(DEFAULT_ISTKSZ)] __attribute__((section(".noinit_kernel"),nocommon));
const size_t _kernel_istksz = ROUND_STK_T(DEFAULT_ISTKSZ);
STK_T *const _kernel_istk = _kernel_istack;

#ifdef TOPPERS_ISTKPT
STK_T *const _kernel_istkpt = TOPPERS_ISTKPT(_kernel_istack, ROUND_STK_T(DEFAULT_ISTKSZ));
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN	_kernel_tmevt_heap[1 + TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];
TMEVTN	*const _kernel_p_tmevt_heap_idle = NULL;

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
	((INIRTN)(_kernel_target_hrt_initialize))((intptr_t)(0));
	((INIRTN)(_kernel_target_twdtimer_initialize))((intptr_t)(0));
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
	((TERRTN)(_kernel_target_twdtimer_terminate))((intptr_t)(0));
	((TERRTN)(_kernel_target_hrt_terminate))((intptr_t)(0));
}

/*
 *  Temporal Partitioning Functions
 */

const RELTIM _kernel_system_cyctim = 0U;
const uint_t _kernel_tnum_schedcb = 0U;
TOPPERS_EMPTY_LABEL(SCHEDCB, _kernel_schedcb_table);
TOPPERS_EMPTY_LABEL(const TWDINIB, _kernel_twdinib_table);
const ID _kernel_tmax_somid = 0;
const SOMINIB *const _kernel_p_inisom = NULL;
TOPPERS_EMPTY_LABEL(const SOMINIB, _kernel_sominib_table);

/*
 *  Protection Domain Management Functions
 */

const ID _kernel_tmax_domid = (TMIN_DOMID + TNUM_DOMID - 1);

const DOMINIB _kernel_dominib_kernel = { TACP_KERNEL, &_kernel_schedcb_kernel, &(_kernel_tmevt_heap[0]), INT_PRIORITY(TMIN_TPRI + 1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL } };

const DOMINIB _kernel_dominib_table[TNUM_DOMID] = {
	{ TACP(DOM1), &_kernel_schedcb_idle, &(_kernel_tmevt_heap[0]), INT_PRIORITY(TMIN_TPRI + 1), { TACP(DOM1), TACP_KERNEL, TACP_KERNEL, TACP(DOM1) } },
	{ TACP(DOM2), &_kernel_schedcb_idle, &(_kernel_tmevt_heap[0]), INT_PRIORITY(TMIN_TPRI + 1), { TACP(DOM2), TACP_KERNEL, TACP_KERNEL, TACP(DOM2) } }
};

