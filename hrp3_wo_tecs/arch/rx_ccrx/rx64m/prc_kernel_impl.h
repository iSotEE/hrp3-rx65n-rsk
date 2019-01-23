/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2016 by Embedded and Real-Time Systems Laboratory
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
 */

/*
 *		kernel_impl.hのプロセッサ依存部（RX64M用）
 *
 *  このヘッダファイルは，target_kernel_impl.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 *
 */

#ifndef TOPPERS_PRC_KERNEL_IMPL_H
#define TOPPERS_PRC_KERNEL_IMPL_H

#include "rx64m.h"
#include "core_kernel_impl.h"

/*
 *  割込み番号の範囲の判定
 *
 *  割込み番号が有効な値か厳密にチェックするため,
 *  コンフィギュレータ出力テーブルを参照する.
 */
#define VALID_INTNO( intno )	(intno <= TMAX_INTNO)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをセットしようとした場合には，FALSEを返す．
 */
Inline bool_t
disable_int( INTNO intno )
{
	/*
	 *  レベル定義が0である場合はCFG_INTされていない
	 */
	if( cfg_int_table[intno].intpri == 0 ){
		return ( false );
	}

	*ICU_IERm_ADDR(intno / 8) &= ~(1U << (intno % 8));

	return ( true );
}

/*
 *  割込み要求禁止フラグのクリア
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，FALSEを返す．
 */
Inline bool_t
enable_int( INTNO intno )
{
	/*
	 *  レベル定義が0である場合はCFG_INTされていない
	 */
	if( cfg_int_table[intno].intpri == 0 ){
		return ( false );
	}

	*ICU_IERm_ADDR(intno / 8) |= (1U << (intno % 8));

	return ( true );
}

/*
 *  割込み要求のクリア
 */
Inline void
clear_int( INTNO intno )
{
	*ICU_IRn_ADDR(intno) = 0U;
}

/*
 *  割込みの要求
 */
Inline void
raise_int(INTNO intno)
{
	*ICU_IRn_ADDR(intno) = 1U;
}

/*
 *  割込み要求のチェック
 */
Inline bool_t
probe_int( INTNO intno )
{
	/*
	 *  割込み要求レジスタは0 or 1でしかないため,
	 *  そのままの値を返す.
	 */
	return ( *ICU_IRn_ADDR(intno) );
}

/*
 *  プロセッサ依存の初期化
 */
extern void prc_initialize(void);

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_PRC_KERNEL_IMPL_H */
