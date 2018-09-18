/* 
 *		全静的APIのテスト(2)
 * 
 *  $Id: cfg_all2.c 314 2018-04-02 21:22:49Z ertl-hiro $
 */

#include "cfg_all2.h"

/*
 *  スタック領域，カーネルの管理領域の定義
 */
STK_T	stack_TASK2[COUNT_STK_T(STACK_SIZE)]
					__attribute__((section(".noinit_kernel"),nocommon));
MPF_T	mpf_MPF2[20 * COUNT_MPF_T(200)]
					__attribute__((section(".noinit_DOM1"),nocommon));

/*
 *  変数の定義
 */
volatile int	var1;
volatile int	var2 __attribute__((section(".bss_DOM1_add2"),nocommon));
volatile int	var3 __attribute__((section(".data_shared"),nocommon)) = 1;

/*
 *  関数の定義
 */
void	task1(intptr_t exinf) { }
void	task2(intptr_t exinf) { }
