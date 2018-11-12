/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2018 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: chip_timer.h 525 2018-11-04 13:12:59Z ertl-hiro $
 */

/*
 *		タイマドライバ（CT11MPcore上でのシステム時刻管理機能テスト用）
 */

#ifndef TOPPERS_CHIP_TIMER_H
#define TOPPERS_CHIP_TIMER_H

#include "kernel/kernel_impl.h"
#include <sil.h>
#include "mpcore.h"

/*
 *  テストプログラムで置き換える関数のリネーム
 */
#define target_hrt_get_current	_kernel_target_hrt_get_current
#define target_hrt_set_event	_kernel_target_hrt_set_event
#define target_hrt_raise_event	_kernel_target_hrt_raise_event

/*
 *  タイマ割込みハンドラ登録のための定数
 */
#define INHNO_TIMER		MPCORE_IRQNO_TMR	/* 割込みハンドラ番号 */
#define INTNO_TIMER		MPCORE_IRQNO_TMR	/* 割込み番号 */
#define INTPRI_TIMER	(TMAX_INTPRI - 1)	/* 割込み優先度 */
#define INTATR_TIMER	TA_NULL				/* 割込み属性 */

/*
 *  タイマの設定値のデフォルト値の定義
 */
#ifndef MPCORE_WDG_LR_VALUE
#define MPCORE_WDG_LR_VALUE		0xffffffffU	/* ウォッチドッグのリロード値 */
#endif /* MPCORE_WDG_LR_VALUE */

#ifndef MPCORE_WDG_FREQ
#define MPCORE_WDG_FREQ			1		/* ウォッチドッグの駆動周波数 */
#endif /* MPCORE_WDG_FREQ */

#ifndef MPCORE_TMR_FREQ
#define MPCORE_TMR_FREQ			1		/* タイマの駆動周波数 */
#endif /* MPCORE_TMR_FREQ */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  高分解能タイマの起動処理
 */
extern void	target_hrt_initialize(intptr_t exinf);

/*
 *  高分解能タイマの停止処理
 */
extern void	target_hrt_terminate(intptr_t exinf);

/*
 *  高分解能タイマの現在のカウント値の読出し
 */
extern HRTCNT target_hrt_get_current(void);

/*
 *  高分解能タイマへの割込みタイミングの設定
 *
 *  高分解能タイマを，hrtcntで指定した値カウントアップしたら割込みを発
 *  生させるように設定する．
 */
extern void target_hrt_set_event(HRTCNT hrtcnt);

/*
 *  高分解能タイマ割込みの要求
 */
extern void target_hrt_raise_event(void);

/*
 *  割込みタイミングに指定する最大値
 */
#ifdef HRT_CONFIG1		/* 1μ秒毎にカウントアップする32ビットタイマ */
#define HRTCNT_BOUND	4000000002U
#endif /* HRT_CONFIG1 */

#ifdef HRT_CONFIG2		/* 10μ毎にカウントアップする16ビットタイマ */
#define HRTCNT_BOUND	(0x10000U * 9U)
#endif /* HRT_CONFIG2 */

/*
 *  高分解能タイマ割込みの要求（テストプログラム用）
 */
extern void target_raise_hrt_int(uint_t timing);

/*
 *  高分解能タイマ割込みハンドラ
 */
extern void	target_hrt_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CHIP_TIMER_H */
