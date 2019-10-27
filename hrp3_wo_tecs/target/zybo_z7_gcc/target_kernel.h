/*
 *		kernel.hのターゲット依存部（ZYBO_Z7用）
 *
 *  このヘッダファイルは，kernel.hからインクルードされる．他のファイル
 *  から直接インクルードすることはない．このファイルをインクルードする
 *  前に，t_stddef.hがインクルードされるので，それに依存してもよい．
 * 
 *  $Id: target_kernel.h 761 2019-09-30 03:18:30Z ertl-honda $
 */

#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

/*
 *  高分解能タイマのタイマ周期
 */
#ifndef USE_64BIT_HRTCNT
/* TCYC_HRTCNTは定義しない．*/
#endif /* USE_64BIT_HRTCNT */

/*
 *  高分解能タイマのカウント値の進み幅
 */
#define TSTEP_HRTCNT	1U

/*
 *  タイムウィンドウの長さに指定できる値の上限
 */
#define TMAX_TWDTIM		858993459U			/* floor(2^32/5) */

/*
 *  オーバランハンドラの残りプロセッサ時間に指定できる最大値
 */
#define TMAX_OVRTIM		858993459U			/* floor(2^32/5) */

/*
 *  チップで共通な定義
 */
#include "chip_kernel.h"

#endif /* TOPPERS_TARGET_KERNEL_H */
