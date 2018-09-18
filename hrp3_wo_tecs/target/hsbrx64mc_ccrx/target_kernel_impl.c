/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2013-2018 by Embedded and Real-Time Systems Laboratory
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
 *		ターゲット依存モジュール（HSBRX64MC用）
 */

#include "kernel_impl.h"
#include "task.h"
#include "hsbrx64mc.h"

/*
 *  ハードウェア固有の初期化ルーチン
 *  クロック回路の初期化を行う。
 */
void
hardware_init_hook(void)
{
#if FREQ_MAIN_CLOCK == 24000000 && FREQ_PCLK_BCD == 60000000 && FREQ_CMTW0 == 7500000
	/*
	 *  クロック設定.
	 *  メインクロック: 24MHz,
	 *  ソースはPLL回路に設定: 24 * 10 = 240MHz,
	 *  ICLK(システムクロック): PLL / 2 = 120MHz,
	 *  FCLK(FlashIFクロック): PLL / 4 = 60MHz,
	 *  BCLK(外部バスクロック): PLL / 2 = 120MHz,
	 *  PCLKA(周辺モジュールクロックA): PLL / 2 = 120MHz,
	 *  PCLKB/C/D(周辺モジュールクロックB/C/D): PLL / 4 = 60MHz,
	 *  UCLK(USBクロック): PLL / 5 = 48MHz.
	 *  CMTW0の周波数: PCLKB / 8 = 7.5MHz.
	 *
	 *  References:
	 *  [1] 9.8 クロックソース切り替え, page 324.
	 */

	/* PRCRで書込み許可 */
	sil_wrh_mem((void *)SYSTEM_PRCR_ADDR,
			SYSTEM_PRCR_PRKEY_BITS | SYSTEM_PRCR_PRC0_BIT | SYSTEM_PRCR_PRC1_BIT);

	/* 1. 内部リセット解除後、MOFCR レジスタの MODRV2[1:0] ビットでドライブ能力を設定 */
	sil_wrb_mem((void *)SYSTEM_MOFCR_ADDR, 0x0);

	/* 2. MOSCWTCR.MSTS[7:0] ビットでメインクロック発振器の発振待機時間を設定 */
	/* TODO: we don't know tMAINOSC (assume MAX) */
	sil_wrb_mem((void *)SYSTEM_MOSCWTCR_ADDR, 0xFF);

	/* 3. MOSCCR レジスタの MOSTP ビットでメインクロック発振器を動作に設定 */
	sil_wrb_mem((void *)SYSTEM_MOSCCR_ADDR, 0x0);
	/* MOSTP ビットまたは MOFCR.MOFXIN ビットの書き換えを行う場合は、書き込みの完了を待ってから、後続の命令を実行するようにしてください */
	while((sil_reb_mem((void *)SYSTEM_MOSCCR_ADDR) & SYSTEM_MOSCCR_MOSTP_BIT) != 0);

	/* 4. PLLCR レジスタで周波数逓倍率を設定（PLL クロックソースの初期設定はメインクロック発振器） */
	sil_wrh_mem((void *)SYSTEM_PLLCR_ADDR, (0x13 << SYSTEM_PLLCR_STC_SHIFT));

	/* 5. PLLCR2 レジスタの PLL 停止制御ビットで PLL 動作を選択 */
	sil_wrb_mem((void *)SYSTEM_PLLCR2_ADDR, 0x0);

	/* 6. OSCOVFSR レジスタの PLOVF フラグで PLL クロックが安定したことを確認 */
	while((sil_reb_mem((void *)SYSTEM_OSCOVFSR_ADDR) & SYSTEM_OSCOVFSR_PLOVF_BIT) == 0);

	/* 7. SCKCR、SCKCR2 レジスタでクロックソース切り替え後の分周比を設定 */
	sil_wrw_mem((void *)SYSTEM_SCKCR_ADDR, (0x2 << SYSTEM_SCKCR_PCLKD_SHIFT) |
			(0x2 << SYSTEM_SCKCR_PCLKC_SHIFT) | (0x2 << SYSTEM_SCKCR_PCLKB_SHIFT) |
			(0x1 << SYSTEM_SCKCR_PCLKA_SHIFT) | (0x1 << SYSTEM_SCKCR_BCK_SHIFT) |
			(0x1 << SYSTEM_SCKCR_ICK_SHIFT) |(0x2 << SYSTEM_SCKCR_FCK_SHIFT));
	sil_wrh_mem((void *)SYSTEM_SCKCR2_ADDR, (0x4 << SYSTEM_SCKCR2_UCK_SHIFT) | 0x1);

	/* 8. SCKCR3 レジスタの CKSEL[2:0] ビットで LOCO クロックから PLL クロックに変更 */
	sil_wrh_mem((void *)SYSTEM_SCKCR3_ADDR, (0x4 << SYSTEM_SCKCR3_CKSEL_SHIFT));

	/* PRCRで書込み禁止 */
	sil_wrh_mem((void *)SYSTEM_PRCR_ADDR, SYSTEM_PRCR_PRKEY_BITS);

	/* Set CMTW0.CMWCR.CTS to match FREQ_CMTW0 */
	sil_wrh_mem((void *)CMTW0_CMWCR_ADDR, (0x0 << CMTWn_CMWCR_CKS_SHIFT));

#else
#error Must modify code above if target frequencies are changed.
#endif
}

/*
 *  本コンパイラではweak definitionの機能が無いため,
 *  特に必要な処理はないが, 必ず呼び出すこととする.
 */
void
software_init_hook(void)
{
}

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	/*
	 *  バナー出力のため、SIO初期化を呼び出す
	 */
	sio_initialize();

	/*
	 * SCI1用ポート設定
	 */

	/* ポートPF0をTxD1, ポートPF2をRxD1に */
	sil_wrb_mem((void *)PORTF_PMR_ADDR , 0x05);

	/* データディレクションレジスタ(PDR)の設定 PF2(RxD1)を入力ポートにする */
	sil_wrb_mem((void *)(PORTF_PDR_ADDR) ,
					sil_reb_mem((void *)(PORTF_PDR_ADDR)) & ~PORTn_PDR_B2_BIT);

	/* データディレクションレジスタ(PDR)の設定 PF0(TxD1)を出力ポートにする */
	sil_wrb_mem((void *)(PORTF_PDR_ADDR) ,
					sil_reb_mem((void *)(PORTF_PDR_ADDR)) & ~PORTn_PDR_B0_BIT);

	/* 書き込みプロテクトレジスタの設定 PFSWEビットへの書き込みを許可 */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR) , 0x00);
	/* 書き込みプロテクトレジスタの設定 PxxFSレジスタへの書き込みを許可 */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR) , MPC_PWPR_PFSWE_BIT);

	/* P21端子機能制御レジスタ PF2をRXD1とする */
	sil_wrb_mem((void *)(MPC_PF2PFS_ADDR) , 0x0a);
	/* P20端子機能制御レジスタ PF0をTXD1とする */
	sil_wrb_mem((void *)(MPC_PF0PFS_ADDR) , 0x0a);

	/* 書き込みプロテクトレジスタの設定 書き込みを禁止 */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR) , MPC_PWPR_B0WI_BIT);
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	while (true);
}
