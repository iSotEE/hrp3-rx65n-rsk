/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2015-2016 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_tprot3.c 200 2016-04-10 16:01:06Z ertl-hiro $
 */

/* 
 *		時間パーティショニングに関するテスト(3)
 *
 * 【テストの目的】
 *
 *  時間パーティショニングを使用した時のシステム動作モードの切換えに関
 *  して，様々な状況を網羅的にテストする．
 *
 * 【テスト項目】
 *
 *	(A) システム動作モードの自動切換え
 *		(A-1) 同じシステム動作モードへの切換え
 *		(A-2) 異なるシステム動作モードへの切換え
 *	(B) 通常のシステム動作モードからのchg_som
 *		(B-1) 通常のシステム動作モードへの切換え
 *		(B-2) システム周期停止モードへの切換え
 *	(C) システム周期停止モードからのchg_som
 *
 * 【使用リソース】
 *
 *	システム周期: (20 * TEST_TIME_CP)
 *	DOM1: SOM1,SOM2,SOM3でタイムウィンドウを割当て
 *	DOM2: SOM1,SOM2でタイムウィンドウを割当て
 *	DOM3: タイムウィンドウを割り当てない
 *	SOM1: 初期モード，遷移先システム動作モード: SOM1，DOM2→DOM1→アイドル
 *	SOM2: 遷移先システム動作モード: SOM3，DOM1→DOM2→アイドル
 *	SOM3: 遷移先システム動作モード: SOM2，DOM1→アイドル
 *	TASK1: DOM1，中優先度，TA_ACT属性
 *	TASK2: DOM2，中優先度，TA_ACT属性
 *	TASK3: DOM3，中優先度，TA_ACT属性
 *	TASK4: カーネルドメイン，低優先度，TA_ACT属性
 *
 * 【テストシーケンス】
 *
 *	// システム動作モード：SOM1
 *	// タイムウィンドウ for DOM2
 *	== TASK2 ==
 *	1:	get_som(&somid)
 *		assert(somid == SOM1)
 *		DO(WAIT(task2_flag))
 *	// タイムウィンドウ for DOM1
 *	== TASK1 ==
 *	2:	DO(WAIT(task1_flag))
 *	// アイドルウィンドウ
 *	== TASK3 ==
 *	3:	DO(SET(task1_flag))
 *		DO(SET(task2_flag))
 *		DO(WAIT(task3_flag))
 *	// システム動作モード：SOM1										... (A-1)
 *	// タイムウィンドウ for DOM2
 *	== TASK2 ==
 *	4:	DO(SET(task3_flag))
 *		chg_som(SOM2)												... (B-1-1)
 *		get_som(&somid)
 *		assert(somid == SOM1)
 *		DO(WAIT(task2_flag))
 *	// タイムウィンドウ for DOM1
 *	== TASK1 ==
 *	5:	DO(WAIT(task1_flag))
 *	// アイドルウィンドウ
 *	== TASK3 ==
 *	6:	DO(SET(task1_flag))
 *		DO(SET(task2_flag))
 *		DO(WAIT(task3_flag))
 *	// システム動作モード：SOM2										... (B-1-2)
 *	// タイムウィンドウ for DOM1
 *	== TASK1 ==
 *	7:	get_som(&somid)
 *		assert(somid == SOM2)
 *		DO(SET(task3_flag))
 *		DO(WAIT(task1_flag))
 *	// タイムウィンドウ for DOM2
 *	== TASK2 ==
 *	8:	DO(WAIT(task2_flag))
 *	// アイドルウィンドウ
 *	== TASK3 ==
 *	9:	DO(SET(task1_flag))
 *		DO(SET(task2_flag))
 *		DO(WAIT(task3_flag))
 *	// システム動作モード：SOM3										... (A-2)
 *	// タイムウィンドウ for DOM1
 *	== TASK1 ==
 *	10:	get_som(&somid)
 *		assert(somid == SOM3)
 *		DO(SET(task3_flag))
 *		DO(WAIT(task1_flag))
 *	// アイドルウィンドウ
 *	== TASK3 ==
 *	11:	DO(SET(task1_flag))
 *		DO(WAIT(task3_flag))
 *	// システム動作モード：SOM2										... (A-2)
 *	// タイムウィンドウ for DOM1
 *	== TASK1 ==
 *	12:	get_som(&somid)
 *		assert(somid == SOM2)
 *		DO(SET(task3_flag))
 *		DO(WAIT(task1_flag))
 *	== TASK2 ==
 *	13:	DO(WAIT(task2_flag))
 *	// アイドルウィンドウ
 *	== TASK3 ==
 *	14:	DO(SET(task1_flag))
 *		DO(SET(task2_flag))
 *		chg_som(TSOM_STP)											... (B-2-1)
 *		get_som(&somid)
 *		assert(somid == SOM2)
 *	15:	DO(WAIT(task3_flag))
 *	// システム動作モード：TSOM_STP									... (B-2-2)
 *	== TASK4 ==
 *	16:	get_som(&somid)
 *		assert(somid == TSOM_STP)
 *		DO(SET(task3_flag))
 *		dly_tsk(TEST_TIME_PROC) ... TASK4が実行再開するまで
 *	// 実行すべきタスクがない
 *	== TASK4 ==
 *	17:	chg_som(SOM1)												... (C)
 *	// システム動作モード：SOM1
 *	// タイムウィンドウ for DOM2
 *	== TASK2 ==
 *	18:	get_som(&somid)
 *		assert(somid == SOM1)
 *		DO(WAIT(task2_flag))
 *	// タイムウィンドウ for DOM1
 *	== TASK1 ==
 *	19:	DO(WAIT(task1_flag))
 *	// アイドルウィンドウ
 *	== TASK3 ==
 *	20:	DO(SET(task1_flag))
 *		DO(SET(task2_flag))
 *	21:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "syssvc/test_svc.h"
#include "kernel_cfg.h"
#include "test_tprot3.h"

volatile bool_t	task1_flag;
volatile bool_t	task2_flag;
volatile bool_t	task3_flag;

#define WAIT(flag)	do { (flag) = false; while (!(flag)); } while (false)
#define SET(flag)	do { (flag) = true; } while (false)

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	ID		somid;

	check_point(2);
	WAIT(task1_flag);

	check_point(5);
	WAIT(task1_flag);

	check_point(7);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM2);

	SET(task3_flag);

	WAIT(task1_flag);

	check_point(10);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM3);

	SET(task3_flag);

	WAIT(task1_flag);

	check_point(12);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM2);

	SET(task3_flag);

	WAIT(task1_flag);

	check_point(19);
	WAIT(task1_flag);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;
	ID		somid;

	test_start(__FILE__);

	check_point(1);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM1);

	WAIT(task2_flag);

	check_point(4);
	SET(task3_flag);

	ercd = chg_som(SOM2);
	check_ercd(ercd, E_OK);

	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM1);

	WAIT(task2_flag);

	check_point(8);
	WAIT(task2_flag);

	check_point(13);
	WAIT(task2_flag);

	check_point(18);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM1);

	WAIT(task2_flag);

	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;
	ID		somid;

	check_point(3);
	SET(task1_flag);

	SET(task2_flag);

	WAIT(task3_flag);

	check_point(6);
	SET(task1_flag);

	SET(task2_flag);

	WAIT(task3_flag);

	check_point(9);
	SET(task1_flag);

	SET(task2_flag);

	WAIT(task3_flag);

	check_point(11);
	SET(task1_flag);

	WAIT(task3_flag);

	check_point(14);
	SET(task1_flag);

	SET(task2_flag);

	ercd = chg_som(TSOM_STP);
	check_ercd(ercd, E_OK);

	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM2);

	check_point(15);
	WAIT(task3_flag);

	check_point(20);
	SET(task1_flag);

	SET(task2_flag);

	check_finish(21);
	check_point(0);
}

void
task4(intptr_t exinf)
{
	ER_UINT	ercd;
	ID		somid;

	check_point(16);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == TSOM_STP);

	SET(task3_flag);

	ercd = dly_tsk(TEST_TIME_PROC);
	check_ercd(ercd, E_OK);

	check_point(17);
	ercd = chg_som(SOM1);
	check_ercd(ercd, E_OK);

	check_point(0);
}
