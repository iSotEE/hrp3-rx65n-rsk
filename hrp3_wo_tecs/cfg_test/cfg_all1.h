/*
 *		全静的APIのテスト(1)
 * 
 *  $Id: cfg_all1.h 676 2019-03-11 04:52:04Z ertl-hiro $
 */

#include <kernel.h>

/*
 *  優先度の定義
 */
#define HIGH_PRIORITY	9		/* 高優先度 */
#define MID_PRIORITY	10		/* 中優先度 */
#define LOW_PRIORITY	11		/* 低優先度 */

#define MAX_INT_PRIORITY	(-1)
#define MIN_INT_PRIORITY	TMIN_INTPRI

/*
 *  割込み番号，割込みハンドラ番号，CPU例外ハンドラ番号の定義
 */
#define INTNO1		4
#define INTNO2		5
#define INTNO3		6
#define INHNO1		4
#define CPUEXC1		1
#define CPUEXC2		2

/*
 *  スタックサイズの定義
 */
#define	STACK_SIZE		4096		/* タスクのスタックサイズ */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  スタック領域，カーネルの管理領域の定義
 */
extern STK_T stack_TASK2[];
extern MPF_T mpf_MPF2[];
extern STK_T istack[];

/*
 *  変数の定義
 */
extern volatile int var1;
extern volatile int var2;

/*
 *  関数のプロトタイプ宣言
 */
extern void	task1(intptr_t exinf);
extern void	task2(intptr_t exinf);
extern void	cyclic1_handler(intptr_t exinf);
extern void	alarm1_handler(intptr_t exinf);
extern void isr1(intptr_t exinf);
extern void isr2(intptr_t exinf);
extern void isr3(intptr_t exinf);
extern void	int1_handler(void);
extern void	cpuexc1_handler(void *p_excinf);
extern void	cpuexc2_handler(void *p_excinf);
extern ER_UINT	extended_svc1(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid);
extern ER_UINT	extended_svc3(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid);
extern void initialize1_routine(intptr_t exinf);
extern void initialize2_routine(intptr_t exinf);
extern void terminate1_routine(intptr_t exinf);
extern void terminate2_routine(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */
