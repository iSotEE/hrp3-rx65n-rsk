/* kernel_mem.c */
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
#include "cfg_all2.h"

/*
 *  Memory Object Initialization Information
 */

extern char __start_mo_text_kernel[];
extern char __start_mo_rodata_kernel[];
extern char __start_mo_text_DOM1[];
extern char __start_mo_text_shared[];
extern char __aend_mo_text_shared[];
extern char __start_mo_rwdata_kernel[];
extern char __start_ustack_TASK1[];
extern char __start_ustack_TOPPERS_RAM_DUMMY1[];
extern char __start_ustack_TASK2[];
extern char __start_mo_rwdata_DOM1[];
extern char __start_mo_rwdata_DOM1_S_1_S[];
extern char __start_mo_rwdata_shared[];
extern char __aend_mo_rwdata_shared[];

const uint_t _kernel_tnum_meminib = 17U;

void *const _kernel_memtop_table[18] = {
	0,
	__start_mo_text_kernel /* 0x01000000 */,
	__start_mo_rodata_kernel /* 0x01009000 */,
	__start_mo_text_DOM1 /* 0x0100a000 */,
	__start_mo_text_shared /* 0x0100b000 */,
	__aend_mo_text_shared /* 0x0100c000 */,
	__start_mo_rwdata_kernel /* 0x01800000 */,
	__start_ustack_TASK1 /* 0x01804000 */,
	__start_ustack_TOPPERS_RAM_DUMMY1 /* 0x01805000 */,
	__start_ustack_TASK2 /* 0x01806000 */,
	__start_mo_rwdata_DOM1 /* 0x01807000 */,
	__start_mo_rwdata_DOM1_S_1_S /* 0x01809000 */,
	__start_mo_rwdata_shared /* 0x0180a000 */,
	__aend_mo_rwdata_shared /* 0x0180b000 */,
	(void *)(0xf0000000) /* 0xf0000000 */,
	(void *)(0xf1000000) /* 0xf1000000 */,
	(void *)(((char *)(0xf1000000)) + (0x1000000)) /* 0xf2000000 */
};

const MEMINIB _kernel_meminib_table[18] = {
	{ TA_NOEXS, 0U, 0U, 0U },
	{ TA_TEXTSEC, 0U, TACP_KERNEL, TACP_KERNEL },
	{ TA_RODATASEC, 0U, TACP_KERNEL, TACP_KERNEL },
	{ TA_TEXTSEC, 0U, TACP(DOM1), TACP(DOM1) },
	{ TA_TEXTSEC, 0U, TACP_SHARED, TACP_SHARED },
	{ TA_NOEXS, 0U, 0U, 0U },
	{ 0x0, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL },
	{ TA_USTACK|(TA_NOINITSEC), TACP(DOM1), TACP(DOM1), TACP(DOM1) },
	{ TA_USTACK|(TA_NOINITSEC), TACP_KERNEL, TACP_KERNEL, TACP_KERNEL },
	{ TA_USTACK|(TA_NOINITSEC), TACP(DOM1), TACP(DOM1), TACP(DOM1) },
	{ 0x0, TACP(DOM1), TACP(DOM1), TACP(DOM1) },
	{ 0x0, TACP_SHARED, TACP(DOM1), TACP_SHARED },
	{ 0x0, TACP_SHARED, TACP_SHARED, TACP_SHARED },
	{ TA_NOEXS, 0U, 0U, 0U },
	{ TA_ATTMEM|(TA_NULL), TACP(DOM1), TACP(DOM1), TACP(DOM1) },
	{ TA_ATTMEM|(TA_NULL), TACP_SHARED, TACP(DOM1), TACP_SHARED },
	{ TA_NOEXS, 0U, 0U, 0U }
};

/*
 *  Data Section Initialization Information
 */

extern char __start_data_shared[];
extern char __end_data_shared[];
extern char __start_idata_shared[];

const uint_t _kernel_tnum_datasec = 1U;

const DATASECINIB _kernel_datasecinib_table[1] = {
	{ __start_data_shared, __end_data_shared, __start_idata_shared }
};

/*
 *  BSS Section Initialization Information
 */

extern char __start_bss_kernel[];
extern char __end_bss_kernel[];
extern char __start_bss_DOM1[];
extern char __end_bss_DOM1[];
extern char __start_bss_DOM1_S_1_S[];
extern char __end_bss_DOM1_S_1_S[];

const uint_t _kernel_tnum_bsssec = 3U;

const BSSSECINIB _kernel_bsssecinib_table[3] = {
	{ __start_bss_kernel, __end_bss_kernel },
	{ __start_bss_DOM1, __end_bss_DOM1 },
	{ __start_bss_DOM1_S_1_S, __end_bss_DOM1_S_1_S }
};

