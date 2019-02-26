### TOPPERS/HRP3 Kernel (without TECS) for HSBRX64MC

### 1. 対応ターゲット

統合開発環境：e² studio  
コンパイラ：CCRX  
アーキテクチャ：RXファミリ  
プロセッサ：RX64M  
ボード：HSBRX64MC  

### 2. ディレクトリ構成

hrp3_wo_tecs/arch/ccrx：CCRXツール依存部  
hrp3_wo_tecs/arch/rx_ccrx/common：CCRX用RXコア依存部  
hrp3_wo_tecs/arch/rx_ccrx/rx64m：RX64Mプロセッサ依存部  
hrp3_wo_tecs/target/hsbrx64mc_ccrx：HSBRX64MCターゲット依存部  
sample1：自動メモリ配置のサンプルプログラムとMakefile  
sample1_mml：手動メモリ配置のサンプルプログラムとMakefile  

### 3. CCRX用RXコア依存部

この依存部はCCRXコンパイラとRXファミリのプロセッサが共通に使用できる部分である。  
主に以下の資料を参考にしている。  
[1] RX Family RXv2 Instruction Set  
[2] RX Family User's Manual: Software  
[3] CC-RX Compiler User's Manual  

| ファイル | 説明 |
| ------ | ------ |
| core_inline_symbols.h | コア依存部のインライン関数用pragma定義[1] |
| core_insn.h | RXコアの特殊命令のインライン関数定義 |
| core_kernel_impl.c/.h | CPUロック、割込み優先度マスク等 |
| core_kernel.h | TMIN_INTPRIのデフォルト値、サポートするカーネル機能 |
| core_sil.h | sil.hのコア依存部、エンディアンはリトルを想定[2] |
| core_start.src | コア共通の初期化ルーチン |
| core_stddef.h | t_stddef.hのコア依存部 |
| core_support.src | ディスパッチャ、割込み、サービスコールと例外の出入口処理 |
| core_svc.h | サービスコール呼出し |
| core_test.h | テストプログラム用、浮動小数点例外の発生 |
| core_inline_symbols.h | 非依存部のインライン関数用pragma定義 |
| core_kernel.trb | Cfgパス2のコア依存部、ベクタテーブル等を生成 |
| core_mem.trb | Cfgパス4のコア依存部、MPU情報等を生成 |
| core_offset.trb | CCRXアセンブラ用オフセットとマクロ定義を生成 |
| Makefile.core | Makefileのコア依存部 |
| rx_mpu_lib.trb | MPU用情報テーブルの作成に関するライブラリ |

注1:  
CCRXでは、関数の定義にInlineを指定してもInline化しないことがあるため、  
#pragma inline <関数名>を使用する必要がある。  
注2:  
RXの命令は常にリトルに固定。  
データのエンディアンを選択できるプロセッサもあるが、デフォルト（リトル）を使用すると想定。  

### 3. RX64Mプロセッサ依存部

この依存部はRX64Mプロセッサのターゲットが共通に使用できる部分である。  
主に以下の資料を参考にしている。  
[1] RX64Mグループ　ユーザーズマニュアル　ハードウェア編  

| ファイル | 説明 |
| ------ | ------ |
| prc_inline_symbols.h | プロセッサ依存部のインライン関数用pragma定義 |
| prc_kernel_impl.c/.h | 割込み有効化と属性設定等 |
| prc_kernel.h | 割込み属性の定義 |
| prc_serial.c/.h/.cfg | SIOドライバ[1] |
| prc_timer.c/.h | タイマドライバ[2] |
| rx64m.h | 割込み番号やI/Oレジスタの定義 |
| start.src | プロセッサ依存の初期化を行って、_core_startへ遷移 |
| Makefile.core | Makefileのプロセッサ依存部 |
| prc_kernel.trb | INTNO_VALIDの定義、INTATRのチェック |

注1:  
シリアルコミュニケーションインタフェース（SCI）を使用。  
通信のフォーマットは8N1に固定。  
注2:  
高分解能タイマはCMTW0、タイムウィンドタイマはCMTW1を使用。  
現時点、オーバランハンドラ機能拡張は未対応。  

### 3. HSBRX64MCターゲット依存部

この依存部はターゲットボードとユーザアプリに依存する部分である。  
主に以下の資料を参考にしている。  
[1] HSBRX64MC シリーズ 取扱説明書  

| ファイル | 説明 |
| ------ | ------ |
| hsbrx64mc.h | クロック周波数とUARTボーレートの定義[1] |
| target_inline_symbols.h | ターゲット依存部のインライン関数用pragma定義 |
| target_kernel_impl.c | ハードウェア、ターゲット初期化[2] |
| target_kernel_impl.h | DEFAULT_ISTKSZの定義、ログ出力箇所の選択 |
| target_kernel.h | prc_kernel.hをインクルード |
| target_serial.h | ターゲットで使用するSIOポートを定義 |
| target_sil.h | core_sil.hをインクルード |
| target_stddef.h | TOPPERS_assert_abortの定義 |
| target_syssvc.h | 出力先のシリアルポートIDの定義 |
| target_test.h | テストプログラム用、割込みに関する定義 |
| target_timer.h | 高分解能タイマの周期、割込み優先度等の定義 |
| Makefile.target | Makefileのターゲット依存部 |
| target_kernel.cfg | prc_timer.cfgをインクルード |
| target_kernel.trb | prc_kernel.trbをインクルード |
| target_mem.cfg | ターゲットのメモリ配置の定義 |
| target_mem.trb | core_mem.trb等をインクルード |
| target_serial.cfg | prc_serial.cfgをインクルード |

注1:  
デフォルトのボーレートは115200bps。  
注2:  
ハードウェア初期化でクロック回路（PLL）を設定する。  
本実装では、PLL、ICLK、FCLK、BCLK、PCLKA、PCLKB、PCLKC、PCLKD、UCLKはMaxで動作するように設定。  
タイマ（CMTW0）の周波数は7.5MHzに設定。  
ターゲット初期化で、ボード依存の設定を行う。  
本実装では、SCI1が使用するポート端子を設定する。  

### 4. Sample1

| ファイル | 説明 |
| ------ | ------ |
| Makefile | CCRXでSample1をビルド |
| busybox.exe | Makefileが使用するUNIXコマンドを提供 |
| map2syms.py | CCRXが生成したmapファイルをsymsに変換 |
| sample1.cfg | Sample1（自動メモリ配置）用cfgファイル |

### 5. Sample1_mml

| ファイル | 説明 |
| ------ | ------ |
| Makefile | CCRXでSample1をビルド |
| busybox.exe | Makefileが使用するUNIXコマンドを提供 |
| map2syms.py | CCRXが生成したmapファイルをsymsに変換 |
| sample1_mml.cfg | Sample1（手動メモリ配置）用cfgファイル |
| section.clnk | セクション配置の定義 |
