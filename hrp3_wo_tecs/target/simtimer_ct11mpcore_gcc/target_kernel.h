/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2006-2019 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  $Id: target_kernel.h 744 2019-07-15 18:59:37Z ertl-hiro $
 */

/*
 *		kernel.hのターゲット依存部
 *		（CT11MPCore＋タイマドライバシミュレータ用）
 *
 *  このヘッダファイルは，kernel.hからインクルードされる．他のファイル
 *  から直接インクルードすることはない．このファイルをインクルードする
 *  前に，t_stddef.hがインクルードされるので，それに依存してもよい．
 */

#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

/*
 *  割込み優先度の範囲
 */
#define TMIN_INTPRI		(-15)		/* 割込み優先度の最小値（最高値）*/
#define TMAX_INTPRI		(-1)		/* 割込み優先度の最大値（最低値）*/

/*
 *  サポートできる機能の定義
 *
 *  ena_int／dis_int／clr_int／ras_int／prb_intとオーバランハンドラを
 *  サポートすることができる．
 */
#define TOPPERS_TARGET_SUPPORT_ENA_INT		/* ena_int */
#define TOPPERS_TARGET_SUPPORT_DIS_INT		/* dis_int */
#define TOPPERS_TARGET_SUPPORT_CLR_INT		/* clr_int */
#define TOPPERS_TARGET_SUPPORT_RAS_INT		/* ras_int */
#define TOPPERS_TARGET_SUPPORT_PRB_INT		/* prb_int */
#define TOPPERS_TARGET_SUPPORT_OVRHDR

/*
 *  高分解能タイマに関するパラメータ
 *
 *  HRTCNT_BOUNDは，本来はカーネル内部でのみ使用するパラメータであり，
 *  target_timer.hで定義すべきであるが，テストプログラムで使用するため，
 *  このファイルで定義している．
 */

/*
 *  1μ秒毎にカウントアップする32ビットタイマ
 */
#ifdef HRT_CONFIG1
/* TCYC_HRTCNTは定義しない．*/			/* 高分解能タイマのタイマ周期 */
#define TSTEP_HRTCNT	1U				/* 高分解能タイマのカウント値の進み幅 */
#define HRTCNT_BOUND	4000000002U		/* 割込みタイミングに指定する最大値 */
#endif /* HRT_CONFIG1 */

/*
 *  10μ毎にカウントアップする16ビットタイマ
 */
#ifdef HRT_CONFIG2
#define TCYC_HRTCNT		(0x10000U * 10U)/* 高分解能タイマのタイマ周期 */
#define TSTEP_HRTCNT	10U				/* 高分解能タイマのカウント値の進み幅 */
#define HRTCNT_BOUND	(0x10000U * 9U)	/* 割込みタイミングに指定する最大値 */
#endif /* HRT_CONFIG2 */

 /*
 *  1μ秒毎にカウントアップする64ビットタイマ
 */
#ifdef HRT_CONFIG3
/* TCYC_HRTCNTは定義しない．*/			/* 高分解能タイマのタイマ周期 */
#define TSTEP_HRTCNT	1U				/* 高分解能タイマのカウント値の進み幅 */
/* HRTCNT_BOUNDは定義しない */			/* 割込みタイミングに指定する最大値 */
#endif /* HRT_CONFIG3 */

/*
 *  スプリアス割込みへの対策
 */
#ifdef TOPPERS_USE_QEMU
#define MPCORE_TMR_CLEAR_INT()		clear_int(MPCORE_IRQNO_TMR)
#endif /* TOPPERS_USE_QEMU */

/*
 *  コアで共通な定義
 */
#include "core_kernel.h"

#endif /* TOPPERS_TARGET_KERNEL_H */
