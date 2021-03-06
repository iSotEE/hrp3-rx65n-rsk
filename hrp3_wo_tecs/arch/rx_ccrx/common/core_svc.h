/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2015 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: core_svc.h 277 2018-03-12 13:51:14Z ertl-hiro $
 */

/*
 *	ソフトウェア割込みによるサービスコール呼出し（CCRX用）
 */

#ifndef TOPPERS_CORE_SVC_H
#define TOPPERS_CORE_SVC_H

/*
 *  svc命令を用いたサービスコールの呼び出し方法
 */

#define	SVC_SERVICE_CALL	1

#ifndef TOPPERS_MACRO_ONLY

#pragma inline_asm _svc_service_call_0
static ER_UINT
_svc_service_call_0(FN fncd) {
	MOV.L	R1, R5
	INT		#SVC_SERVICE_CALL
}

#pragma inline_asm _svc_service_call_1
static ER_UINT
_svc_service_call_1(intptr_t par1, FN fncd) {
	MOV.L	R2, R5
	INT		#SVC_SERVICE_CALL
}

#pragma inline_asm _svc_service_call_2
static ER_UINT
_svc_service_call_2(intptr_t par1, intptr_t par2, FN fncd) {
	MOV.L	R3, R5
	INT		#SVC_SERVICE_CALL
}

#pragma inline_asm _svc_service_call_3
static ER_UINT
_svc_service_call_3(intptr_t par1, intptr_t par2, intptr_t par3, FN fncd) {
	MOV.L	R4, R5
	INT		#SVC_SERVICE_CALL
}

#pragma inline_asm _svc_service_call_4
static ER_UINT
_svc_service_call_4(intptr_t par1, intptr_t par2, intptr_t par3, intptr_t par4, FN fncd) {
	MOV.L	0[SP], R5
	INT		#SVC_SERVICE_CALL
}

#pragma inline_asm _svc_service_call_5
static ER_UINT
_svc_service_call_5(intptr_t par1, intptr_t par2, intptr_t par3, intptr_t par4, intptr_t par5, FN fncd) {
	MOV.L	0[SP], R14
	MOV.L	4[SP], R5
	INT		#SVC_SERVICE_CALL
}

#ifdef UINT64_MAX
#pragma inline_asm _svc_service_call_1_systim
static ER_UINT
_svc_service_call_1_systim(SYSTIM par1, FN fncd) {
	MOV.L	R3, R5
	INT		#SVC_SERVICE_CALL
}
#endif

#define CAL_SVC_0M(TYPE, FNCD) \
		return ((TYPE)_svc_service_call_0(FNCD))

#define CAL_SVC_1M(TYPE, FNCD, TYPE1, PAR1) \
		return ((TYPE)_svc_service_call_1((intptr_t)(PAR1), FNCD))

#define CAL_SVC_2M(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2) \
		return ((TYPE)_svc_service_call_2((intptr_t)(PAR1), (intptr_t)(PAR2), FNCD))

#define CAL_SVC_3M(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2, TYPE3, PAR3) \
		return ((TYPE)_svc_service_call_3((intptr_t)(PAR1), (intptr_t)(PAR2), (intptr_t)(PAR3), FNCD))

#define CAL_SVC_4M(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2, TYPE3, PAR3, TYPE4, PAR4) \
		return ((TYPE)_svc_service_call_4((intptr_t)(PAR1), (intptr_t)(PAR2), (intptr_t)(PAR3), (intptr_t)(PAR4), FNCD))

#define CAL_SVC_5M(TYPE, FNCD, TYPE1, PAR1, TYPE2, PAR2, TYPE3, PAR3, TYPE4, PAR4, TYPE5, PAR5) \
		return ((TYPE)_svc_service_call_5((intptr_t)(PAR1), (intptr_t)(PAR2), (intptr_t)(PAR3), (intptr_t)(PAR4), (intptr_t)(PAR5), FNCD))

#define CAL_SVC_1M_SYSTIM(TYPE, FNCD, TYPE1, PAR1) \
		return ((TYPE)_svc_service_call_1_systim((TYPE1)(PAR1), FNCD))

/*
 *  サービスコール呼出し関数の展開
 */
#ifndef TOPPERS_SVC_CALL
#include "arch/ccrx/tool_svc.h"
#endif /* TOPPERS_SVC_CALL */

/*
 *  cal_svcサービスコールの呼出し
 */
Inline ER_UINT
cal_svc(FN fncd, intptr_t par1, intptr_t par2,
							intptr_t par3, intptr_t par4, intptr_t par5)
{
	if (fncd > 0) {
		CAL_SVC_5M(ER_UINT, fncd, intptr_t, par1, intptr_t, par2,
							intptr_t, par3, intptr_t, par4, intptr_t, par5);
	}
	else {
		return(E_RSFN);
	}
}

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CORE_SVC_H */
