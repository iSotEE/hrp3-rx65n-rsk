/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2008-2018 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: domain.c 443 2018-08-17 16:18:59Z ertl-hiro $
 */

/*
 *		保護ドメイン管理モジュール
 */

#include "kernel_impl.h"
#include "check.h"
#include "time_event.h"
#include "task.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_CHG_SOM_ENTER
#define LOG_CHG_SOM_ENTER(somid)
#endif /* LOG_CHG_SOM_ENTER */

#ifndef LOG_CHG_SOM_LEAVE
#define LOG_CHG_SOM_LEAVE(ercd)
#endif /* LOG_CHG_SOM_LEAVE */

#ifndef LOG_GET_SOM_ENTER
#define LOG_GET_SOM_ENTER(p_somid)
#endif /* LOG_GET_SOM_ENTER */

#ifndef LOG_GET_SOM_LEAVE
#define LOG_GET_SOM_LEAVE(ercd)
#endif /* LOG_GET_SOM_LEAVE */

#ifdef TOPPERS_domini

/*
 *  現在スケジューリングドメイン
 */
SCHEDCB		*p_twdsched;

/*
 *  アイドル時スケジューリングドメイン
 */
SCHEDCB		*p_idlesched;

/*
 *  カーネルドメインに対応するスケジューリングドメイン管理ブロック
 */
SCHEDCB		schedcb_kernel;

/*
 *  アイドルドメインに対応するスケジューリングドメイン管理ブロック
 */
SCHEDCB		schedcb_idle;

/*
 *  現在のシステム動作モード
 */
const SOMINIB	*p_cursom;

/*
 *  次のシステム動作モード
 */
const SOMINIB	*p_nxtsom;

/*
 *  システム周期を管理するためのタイムイベントブロック
 */
TMEVTB	scyc_tmevtb;

/*
 *  システム周期切換え処理を実行したことを示すフラグ
 */
bool_t	proc_scycswitch;

/*
 *  システム周期切換え処理を保留していることを示すフラグ
 */
bool_t	pending_scycswitch;

/*
 *  実行中のタイムウィンドウ
 */
const TWDINIB	*p_runtwd;

/*
 *  システム周期の最初のタイムウィンドウへの切換えを要求
 */
bool_t	newscyc_twdswitch;

/*
 *  タイムウィンドウ切換え処理を保留していることを示すフラグ
 */
bool_t	pending_twdswitch;

/*
 *  タイムウィンドウタイマを動作させるべき状態であることを示すフラグ
 */
bool_t	twdtimer_enable;

/*
 *  タイムウィンドウタイマが動作中かを示すフラグ
 */
bool_t	twdtimer_flag;

/*
 *  タイムウィンドウの残り時間
 */
PRCTIM	left_twdtim;

/*
 *  実行中の保護ドメインのビットパターン
 */
ACPTN	rundom;

/*
 *  MMU/MPUに設定されている保護ドメイン
 */
const DOMINIB	*p_ctxdom;

/*
 *  スケジューリングドメイン管理ブロックの初期化
 */
static void
initialize_schedcb(SCHEDCB *p_schedcb)
{
	uint_t	i;

	p_schedcb->p_predtsk = NULL;
	for (i = 0; i < TNUM_TPRI; i++) {
		queue_initialize(&(p_schedcb->ready_queue[i]));
	}
	p_schedcb->ready_primap = 0U;
}

/*
 *  保護ドメイン管理モジュールの初期化
 */
void
initialize_domain(void)
{
	uint_t	i;

	initialize_schedcb(&schedcb_kernel);
	initialize_schedcb(&schedcb_idle);
	for (i = 0; i < tnum_schedcb; i++) {
		initialize_schedcb(&(schedcb_table[i]));
	}

	pending_scycswitch = false;
	p_runtwd = NULL;
	newscyc_twdswitch = false;
	pending_twdswitch = false;
	twdtimer_enable = false;
	twdtimer_flag = false;
	rundom = TACP_KERNEL;
	p_ctxdom = NULL;

	p_cursom = p_inisom;
	if (system_cyctim == 0U) {
		/*
		 *  時間パーティショニングを使用しない場合
		 */
		p_twdsched = &schedcb_idle;
		p_idlesched = &schedcb_idle;
	}
	else {
		/*
		 *  時間パーティショニングを使用する場合
		 */
		scyc_tmevtb.callback = (CBACK) scyc_switch;
		scyc_tmevtb.arg = (void *) NULL;

		p_twdsched = &schedcb_kernel;
		p_idlesched = &schedcb_kernel;

		if (p_cursom != NULL) {
			/*
			 *  初期システム動作モードが定義されている場合
			 */
			scyc_tmevtb.evttim = system_cyctim;
			tmevtb_register(&scyc_tmevtb, p_tmevt_heap_kernel);
			p_nxtsom = p_cursom->p_nxtsom;

			/*
			 *  タイムウィンドウ切換え処理の起動を要求
			 *
			 *  この時点では，タイムウィンドウタイマの初期化ができてい
			 *  ないため，タイムウィンドウタイマの動作を開始できない．
			 */
			newscyc_twdswitch = true;
		}
	}
}

#endif /* TOPPERS_domini */

/*
 *  タイムウィンドウタイマの動作開始
 */
#ifdef TOPPERS_twdsta
#ifndef OMIT_TWDTIMER_START

void
twdtimer_start(void)
{
	if (!twdtimer_flag) {
		target_twdtimer_start(left_twdtim);
		twdtimer_flag = true;
	}
}

#endif /* OMIT_TWDTIMER_START */
#endif /* TOPPERS_twdsta */

/*
 *  タイムウィンドウタイマの停止
 */
#ifdef TOPPERS_twdstp
#ifndef OMIT_TWDTIMER_STOP

void
twdtimer_stop(void)
{
	if (twdtimer_flag) {
		left_twdtim = target_twdtimer_stop();
		twdtimer_flag = false;
	}
}

#endif /* OMIT_TWDTIMER_STOP */
#endif /* TOPPERS_twdstp */

/*
 *  タイムウィンドウタイマの切換え
 */
#ifdef TOPPERS_twdcntrl
#ifndef OMIT_TWDTIMER_CONTROL

void
twdtimer_control(void)
{
	if (p_runtsk == NULL || p_runtsk->p_dominib != &dominib_kernel) {
		/*
		 *  実行状態のタスクがないか，実行状態のタスクがユーザドメイン
		 *  に属する場合，タイムウィンドウタイマを動作開始する．
		 */
		if (!twdtimer_flag) {
			target_twdtimer_start(left_twdtim);
			twdtimer_flag = true;
		}
	}
	else {
		/*
		 *  実行状態のタスクがカーネルドメインに属する場合，タイムウィ
		 *  ンドウタイマを停止する．
		 */
		if (twdtimer_flag) {
			left_twdtim = target_twdtimer_stop();
			twdtimer_flag = false;
		}
	}
}

#endif /* OMIT_TWDTIMER_CONTROL */
#endif /* TOPPERS_twdcntrl */

/*
 *  システム周期切換え処理
 *
 *  この関数は，CPUロック状態で呼び出される．
 */
#ifdef TOPPERS_scycswitch

void
scyc_switch(void)
{
	if (p_runtwd != NULL) {
		/*
		 *  システム周期オーバラン
		 */
		twdtimer_stop();
		raise_scycovr_exception();
		pending_twdswitch = false;
	}

	if (dspflg) {
		p_cursom = p_nxtsom;
		p_runtwd = NULL;
		twdtimer_enable = false;
		if (p_cursom == NULL) {
			/*
			 *  システム周期を停止させる場合
			 */
			p_twdsched = &schedcb_kernel;
			p_idlesched = &schedcb_kernel;
			update_schedtsk();
			if (p_runtsk != p_schedtsk) {
				request_dispatch();
			}
		}
		else {
			/*
			 *  システム周期の開始
			 */
			scyc_tmevtb.evttim += system_cyctim;
			tmevtb_register(&scyc_tmevtb, p_tmevt_heap_kernel);
			p_nxtsom = p_cursom->p_nxtsom;

			/*
			 *  タイムウィンドウ切換え処理の要求
			 */
			newscyc_twdswitch = true;
			target_twdtimer_raise_int();
		}
		proc_scycswitch = true;
	}
	else {
		pending_scycswitch = true;
	}
}

#endif /* TOPPERS_scycswitch */

/*
 *  タイムウィンドウ切換え処理
 */
#ifdef TOPPERS_twdswitch

static void
proc_tmevt_heap(TMEVTN *p_tmevt_heap)
{
	proc_scycswitch = false;

	/*
	 *  通知ハンドラが登録されている場合，CPUロック解除状態で呼び出す．
	 */
	if (p_runtwd != NULL && p_runtwd->nfyhdr != NULL) {
		unlock_cpu();
		(*(p_runtwd->nfyhdr))(p_runtwd->exinf);
		lock_cpu();
	}

	/*
	 *  システム周期切換え処理が実行されず，処理中にタイムウィンドウの
	 *  時間を使い切っていない場合，先頭のタイムイベントを処理する．
	 */
	while (!proc_scycswitch
			&& !(twdtimer_enable && target_twdtimer_get_current() == 0U)
			&& tmevt_proc_top(p_tmevt_heap)) ;
}

void
twd_switch(void)
{
	TMEVTN	*p_tmevt_heap;

	lock_cpu();
	if ((twdtimer_enable && left_twdtim == 0U) || newscyc_twdswitch
													|| pending_twdswitch) {
		if (dspflg) {
			if (newscyc_twdswitch) {
				/*
				 *  システム周期の最初のタイムウィンドウに
				 */
				p_runtwd = p_cursom->p_twdinib;
				newscyc_twdswitch = false;
			}
			else {
				/*
				 *  次のタイムウィンドウに
				 */
				p_runtwd += 1;
			}
			if (p_runtwd < (p_cursom + 1)->p_twdinib) {
				/*
				 *  次のタイムウィンドウがある場合
				 */
				p_twdsched = p_runtwd->p_dominib->p_schedcb;
				p_tmevt_heap = p_runtwd->p_dominib->p_tmevt_heap;
				twdtimer_enable = true;
				left_twdtim = p_runtwd->twdlen;
				p_idlesched = &schedcb_idle;
				twdtimer_start();
			}
			else {
				/*
				 *  次のタイムウィンドウがない場合は，アイドルウィンドウに
				 */
				p_runtwd = NULL;
				p_twdsched = &schedcb_idle;
				p_tmevt_heap = p_tmevt_heap_idle;
				twdtimer_enable = false;
				p_idlesched = &schedcb_idle;
			}
			update_schedtsk();
			if (p_runtsk != p_schedtsk) {
				request_dispatch();
			}
			proc_tmevt_heap(p_tmevt_heap);
			pending_twdswitch = false;
		}
		else {
			/*
			 *  タイムウィンドウ切換え処理を保留
			 */
			pending_twdswitch = true;
			twdtimer_enable = false;
		}
	}
	else {
		/*
		 *  このルーチンが呼び出される前に，タイムウィンドウの切換えが
		 *  キャンセルされた場合
		 */
		syslog_2(LOG_ERROR, "spurious (p_runtwd = %x, left_twdtim = %u)",
										(uintptr_t) p_runtwd, left_twdtim);
	}
	unlock_cpu();
}

#endif /* TOPPERS_twdswitch */

/*
 *  タスクディスパッチ可能状態への遷移
 */
#ifdef TOPPERS_setdspflg

void
set_dspflg(void)
{
	dspflg = true;

	if (pending_scycswitch) {
		/*
		 *  保留していたシステム周期切換え処理を実行
		 */
		if (p_runtwd != NULL) {
			/*
			 *  システム周期オーバラン
			 */
			twdtimer_stop();
			raise_scycovr_exception();
			pending_twdswitch = false;
		}

		p_cursom = p_nxtsom;
		p_runtwd = NULL;
		twdtimer_enable = false;
		if (p_cursom == NULL) {
			/*
			 *  システム周期を停止させる場合
			 */
			p_twdsched = &schedcb_kernel;
			p_idlesched = &schedcb_kernel;
		}
		else {
			/*
			 *  システム周期の開始
			 */
			scyc_tmevtb.evttim += system_cyctim;
			tmevtb_register(&scyc_tmevtb, &(_kernel_tmevt_heap[0]));
			p_nxtsom = p_cursom->p_nxtsom;

			/*
			 *  タイムウィンドウ切換え処理の要求
			 */
			newscyc_twdswitch = true;
			target_twdtimer_raise_int();
		}
		pending_scycswitch = false;
	}
	else if (pending_twdswitch) {
		/*
		 *  タイムウィンドウ切換え処理を起動
		 */
		target_twdtimer_raise_int();
	}

	/*
	 *  実行すべきタスクの更新
	 */
	update_schedtsk();
}

#endif /* TOPPERS_setdspflg */

/*
 *  システム動作モードの変更［NGKI5030］
 */
#ifdef TOPPERS_chg_som

ER
chg_som(ID somid)
{
	const SOMINIB	*p_sominib;
	ER				ercd;

	LOG_CHG_SOM_ENTER(somid);
	CHECK_TSKCTX_UNL();							/*［NGKI5031］［NGKI5032］*/
	CHECK_OBJ(system_cyctim != 0U);				/*［NGKI5035］*/
	if (somid == TSOM_STP) {					/*［NGKI5038］*/
		p_sominib = NULL;
	}
	else {
		CHECK_ID(VALID_SOMID(somid));			/*［NGKI5033］*/
		p_sominib = get_sominib(somid);
	}
	CHECK_ACPTN(sysstat_acvct.acptn1);			/*［NGKI5034］*/

	lock_cpu();
	if (p_cursom == NULL) {
		if (p_sominib != NULL) {
			p_cursom = p_sominib;				/*［NGKI5037］*/
			tmevtb_enqueue(&scyc_tmevtb, system_cyctim, p_tmevt_heap_kernel);
			p_nxtsom = p_cursom->p_nxtsom;

			/*
			 *  タイムウィンドウ切換え処理を起動する．
			 */
			p_runtwd = NULL;
			newscyc_twdswitch = true;
			twdtimer_enable = false;
			target_twdtimer_raise_int();
		}
	}
	else {
		p_nxtsom = p_sominib;					/*［NGKI5036］*/
	}
	ercd = E_OK;
	unlock_cpu();

  error_exit:
	LOG_CHG_SOM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_chg_som */

/*
 *  システム動作モードの参照［NGKI5060］
 */
#ifdef TOPPERS_get_som

ER
get_som(ID *p_somid)
{
	ER		ercd;

	LOG_GET_SOM_ENTER(p_somid);
	CHECK_TSKCTX_UNL();							/*［NGKI5061］［NGKI5062］*/
	CHECK_OBJ(system_cyctim != 0U);				/*［NGKI5065］*/
	CHECK_MACV_WRITE(p_somid, ID);				/*［NGKI5064］*/
	CHECK_ACPTN(sysstat_acvct.acptn4);			/*［NGKI5063］*/

	lock_cpu();
	*p_somid = (p_cursom == NULL) ? TSOM_STP : SOMID(p_cursom);
	ercd = E_OK;								/*［NGKI5066］*/
	unlock_cpu();

  error_exit:
	LOG_GET_SOM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_get_som */
