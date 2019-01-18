#
#  TOPPERS/HRP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      High Reliable system Profile Kernel
# 
#  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2006-2018 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
# 
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
# 
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
# 
#  $Id: Makefile_mml 368 2018-04-15 02:31:25Z ertl-hiro $
# 

#
# Compiler (ccrx) dependent functions
#
define compiler_cc # 1: src file, 2: cflags
$(CC) $(patsubst -D%,-define=%,$(patsubst -I%,-include=%,$(2))) $(1)
endef
define compiler_as # 1: src file, 2: asflags
$(AS) -debug $(patsubst -D%,-define=%,$(patsubst -I%,-include=%,$(2) $(INCLUDES))) -output=$@ $(1)
endef
define linker # 1: output, 2: input, 3: cflags, 4: ldflags
$(LINK) -debug $(4) -list=$(1).map -show=symbol -output=$(1) $(2)
endef
define archive # 1: lib file name, 2: obj files
$(LINK) -form=library=u -output=$(1) $(2)
endef
define obj2srec # 1: obj file name, 2: srec file name
$(LINK) $(1) -form=stype -output=$(2)
endef
define obj2syms # 1: obj file name, 2: syms file name
$(PYTHON) map2syms.py $(1).map $(2)
endef
PYTHON = $(E2STUDIODIR)\eclipse\features\com.renesas.python.win32.x86_2.7.12.002\python\python.exe
SED = $(E2STUDIODIR)\Utilities\sed.exe
CC_CONVERTER = $(E2STUDIODIR)\Utilities\ccrx\renesas_cc_converter.exe
TOUCH = busybox touch
OBJ_LDFLAGS += -subcommand=section.clnk

#
#  ターゲットの指定（Makefile.targetで上書きされるのを防ぐため）
#
all: clean

#
#  ターゲット略称の定義
#
TARGET = hsbrx64mc_ccrx

#
#  プログラミング言語の定義
#
SRCLANG = c
#ifeq ($(SRCLANG),c)
#	LIBS = -lc
#endif
ifeq ($(SRCLANG),c++)
	USE_CXX = true
#	CXXLIBS = -lstdc++ -lm -lc
#	CXXRTS = cxxrt.obj newlibrt.obj
endif

#
#  ソースファイルのディレクトリの定義
#
SRCDIR = ../hrp3_wo_tecs

#
#  オブジェクトファイル名の拡張子の設定
#
OBJEXT = abs

#
#  カーネルライブラリ（libkernel.a）のディレクトリ名
#  （カーネルライブラリもmake対象にする時は，空に定義する）
#
KERNEL_LIB = 

#
#  手動メモリ配置を採るかどうかの定義
#
ML_MANUAL = true

#
#  カーネルを関数単位でコンパイルするかどうかの定義
#
KERNEL_FUNCOBJS = 

#
#  TECSを外すかどうかの定義
#
OMIT_TECS = true

#
#  TECS関係ファイルのディレクトリの定義
#
TECSDIR = $(SRCDIR)/tecsgen

#
#  トレースログを取得するかどうかの定義
#
ENABLE_TRACE = 

#
#  開発ツール（コンパイラ等）のディレクトリの定義
#
DEVTOOLDIR = 

#
#  ユーティリティプログラムの名称
#
CFG = ruby $(SRCDIR)/cfg/cfg.rb
TECSGEN = ruby $(TECSDIR)/tecsgen.rb

#
#  オブジェクトファイル名の定義
#
OBJNAME = hrp
ifdef OBJEXT
	OBJFILE = $(OBJNAME).$(OBJEXT)
	CFG1_OUT = cfg1_out.$(OBJEXT)
else
	OBJFILE = $(OBJNAME)
	CFG1_OUT = cfg1_out
endif

#
#  依存関係ファイルを置くディレクトリの定義
#
DEPDIR = deps

#
#  ターゲット依存部のディレクトリの定義
#
TARGETDIR = $(SRCDIR)/target/$(TARGET)

#
#  ターゲット依存の定義のインクルード
#
include $(TARGETDIR)/Makefile.target

#
#  TECS生成ファイルのディレクトリの定義
#
TECSGENDIR = ./gen
ifndef OMIT_TECS
	TECSGEN_TIMESTAMP = $(TECSGENDIR)/tecsgen.timestamp
	INIT_TECS_COBJ = init_tecs.obj
endif

#
#  TECSが生成する定義のインクルード
#
ifndef OMIT_TECS
	GEN_DIR = $(TECSGENDIR)
	-include $(TECSGENDIR)/Makefile.tecsgen
endif

#
#  共通コンパイルオプションの定義
#
COPTS := -debug  $(COPTS)
ifndef OMIT_WARNING_ALL
	COPTS := $(COPTS)
endif
ifndef OMIT_OPTIMIZATION
	COPTS := $(COPTS) -optimize=0
endif
ifdef ML_MANUAL
	CDEFS := -DTOPPERS_ML_MANUAL $(CDEFS)
endif
ifdef OMIT_TECS
	CDEFS := -DTOPPERS_OMIT_TECS $(CDEFS)
endif
CDEFS := $(CDEFS) 
INCLUDES := -I. -I$(SRCDIR)/include $(INCLUDES) -I$(SRCDIR)
LDFLAGS := $(LDFLAGS) 
LIBS := $(LIBS) $(CXXLIBS)
CFLAGS = $(COPTS) $(CDEFS) $(INCLUDES)

#
#  アプリケーションプログラムに関する定義
#
APPLNAME = sample1
APPLDIRS = $(SRCDIR)/sample
APPL_CFG = sample1_mml.cfg
APPL_CDL = sample1.cdl

APPL_DIRS := $(APPLDIRS) $(SRCDIR)/library
APPL_ASMOBJS :=
ifdef USE_CXX
	APPL_CXXOBJS := sample1.obj
	APPL_COBJS :=
else
	APPL_COBJS := sample1.obj
endif
APPL_COBJS := $(APPL_COBJS) $(TECS_USER_COBJS) $(TECS_OUTOFDOMAIN_COBJS) \
				log_output.obj vasyslog.obj t_perror.obj strerror.obj
APPL_CFLAGS := $(APPL_CFLAGS)
ifdef APPLDIRS
	INCLUDES := $(INCLUDES) $(foreach dir,$(APPLDIRS),-I$(dir))
endif

#
#  システムサービスに関する定義
#
SYSSVC_DIRS := $(TECSGENDIR) $(SRCDIR)/tecs_kernel \
				$(SYSSVC_DIRS) $(SRCDIR)/syssvc \
				$(TECSDIR)/tecs $(TECSDIR)/tecs/rpc
SYSSVC_ASMOBJS := $(SYSSVC_ASMOBJS)
SYSSVC_COBJS := $(SYSSVC_COBJS) syslog.obj banner.obj serial.obj logtask.obj $(TECS_KERNEL_COBJS) \
				$(INIT_TECS_COBJ) $(CXXRTS)
SYSSVC_CFLAGS := $(SYSSVC_CFLAGS) -DTOPPERS_SVC_CALL
INCLUDES := $(INCLUDES) -I$(TECSGENDIR) -I$(SRCDIR)/tecs_kernel \
				-I$(TECSDIR)/tecs -I$(TECSDIR)/tecs/rpc

#
#  ターゲットファイル
#
.PHONY: all
ifndef OMIT_TECS
all: tecs
	@$(MAKE) kernel_cfg.h $(OFFSET_H) check
#	@$(MAKE) kernel_cfg.h $(OFFSET_H) check $(OBJNAME).bin
#	@$(MAKE) kernel_cfg.h $(OFFSET_H) check $(OBJNAME).srec
else
all: kernel_cfg.h $(OFFSET_H) check
#all: kernel_cfg.h $(OFFSET_H) check $(OBJNAME).bin
#all: kernel_cfg.h $(OFFSET_H) check $(OBJNAME).srec
endif

##### 以下は編集しないこと #####

#
#  コンフィギュレータに関する定義
#
CFG_KERNEL := --kernel hrp
CFG_TABS := --api-table $(SRCDIR)/kernel/kernel_api_mml.def \
			--symval-table $(SRCDIR)/kernel/kernel_sym.def $(CFG_TABS)
CFG_ASMOBJS := $(CFG_ASMOBJS)
CFG_COBJS := kernel_cfg.obj kernel_mem.obj $(CFG_COBJS)
CFG_OBJS := $(CFG_ASMOBJS) $(CFG_COBJS)
CFG2_OUT_SRCS := kernel_cfg.h kernel_cfg.c kernel_mem.c $(CFG2_OUT_SRCS)
CFG_CFLAGS := -DTOPPERS_CB_TYPE_ONLY $(CFG_CFLAGS)

#
#  カーネルに関する定義
#
#  KERNEL_ASMOBJS: カーネルライブラリに含める，ソースがアセンブリ言語の
#				   オブジェクトファイル．
#  KERNEL_COBJS: カーネルのライブラリに含める，ソースがC言語で，ソース
#				 ファイルと1対1に対応するオブジェクトファイル．
#  KERNEL_LCSRCS: カーネルのライブラリに含めるC言語のソースファイルで，
#				  1つのソースファイルから複数のオブジェクトファイルを生
#				  成するもの．
#  KERNEL_LCOBJS: 上のソースファイルから生成されるオブジェクトファイル．
#
KERNEL_DIRS := $(KERNEL_DIRS) $(SRCDIR)/kernel
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS)
KERNEL_COBJS := $(KERNEL_COBJS) svc_table.obj
KERNEL_CFLAGS := $(KERNEL_CFLAGS) -I$(SRCDIR)/kernel

#
#  カーネルのファイル構成の定義
#
include $(SRCDIR)/kernel/Makefile.kernel
ifdef KERNEL_FUNCOBJS
	KERNEL_LCSRCS := $(KERNEL_FCSRCS)
	KERNEL_LCOBJS := $(foreach file,$(KERNEL_FCSRCS),$($(file:.c=)))
else
	KERNEL_CFLAGS := -DALLFUNC $(KERNEL_CFLAGS)
	KERNEL_COBJS := $(KERNEL_COBJS) \
					$(foreach file,$(KERNEL_FCSRCS),$(file:.c=.obj))
endif
ifdef OMIT_OFFSET_H
	OFFSET_H =
else
	OFFSET_H = offset.h
endif
ifndef TARGET_OFFSET_TRB
	TARGET_OFFSET_TRB := $(TARGETDIR)/target_offset.trb
endif
ifndef TARGET_KERNEL_TRB
	TARGET_KERNEL_TRB := $(TARGETDIR)/target_kernel.trb
endif
ifndef TARGET_CHECK_TRB
	TARGET_CHECK_TRB := $(TARGETDIR)/target_check.trb
endif
ifndef TARGET_KERNEL_CFG
	TARGET_KERNEL_CFG := $(TARGETDIR)/target_kernel.cfg
endif

#ifndef LDSCRIPT
#	LDSCRIPT = ldscript.ld
#endif

#
#  ソースファイルのあるディレクトリに関する定義
#
vpath %.c $(KERNEL_DIRS) $(SYSSVC_DIRS) $(APPL_DIRS)
vpath %.src $(KERNEL_DIRS) $(SYSSVC_DIRS) $(APPL_DIRS)
vpath %.cfg $(APPL_DIRS)
vpath %.cdl $(APPL_DIRS)

#
#  コンパイルのための変数の定義
#
KERNEL_LIB_OBJS = $(KERNEL_ASMOBJS) $(KERNEL_COBJS) $(KERNEL_LCOBJS)
SYSSVC_OBJS = $(SYSSVC_ASMOBJS) $(SYSSVC_COBJS)
APPL_OBJS = $(APPL_ASMOBJS) $(APPL_COBJS) $(APPL_CXXOBJS)
ALL_OBJS = $(START_OBJS) $(APPL_OBJS) $(SYSSVC_OBJS) $(CFG_OBJS) \
											$(END_OBJS) $(HIDDEN_OBJS)
ALL_LIBS = $(LIBS)
ifdef KERNEL_LIB
	LIBS_DEP = $(KERNEL_LIB)/libkernel.a $(filter %.a,$(LIBS))
	ALL_LIBS += -library=$(KERNEL_LIB)/libkernel.a
	REALCLEAN_FILES := libkernel.a $(REALCLEAN_FILES)
else
	LIBS_DEP = libkernel.a $(filter %.a,$(LIBS))
	ALL_LIBS += -library=libkernel.a
endif

ifdef TEXT_START_ADDRESS
	LDFLAGS := $(LDFLAGS) -Wl,-Ttext,$(TEXT_START_ADDRESS)
endif
ifdef DATA_START_ADDRESS
	LDFLAGS := $(LDFLAGS) -Wl,-Tdata,$(DATA_START_ADDRESS)
endif
ifdef CFG1_OUT_LDSCRIPT
	CFG1_OUT_LDFLAGS := $(CFG1_OUT_LDFLAGS) -Wl,-T,$(CFG1_OUT_LDSCRIPT)
endif

#
#  tecsgenからCプリプロセッサを呼び出す際のオプションの定義
#
TECS_CPP = $(CC) $(CDEFS) $(INCLUDES) $(SYSSVC_CFLAGS) -D TECSGEN -E

#
#  tecsgenの呼出し
#
.PHONY: tecs
tecs $(TECSGEN_SRCS) $(TECS_HEADERS): $(TECSGEN_TIMESTAMP) ;
$(TECSGEN_TIMESTAMP): $(APPL_CDL) $(TECS_IMPORTS)
	$(TECSGEN) $< -R $(INCLUDES) --cpp "$(TECS_CPP)" -g $(TECSGENDIR)

#
#  omit_svc.hの生成規則（ファイルがなければ空のファイルを生成する）
#
omit_svc.h:
	$(TOUCH) omit_svc.h

#
#  カーネルのコンフィギュレーションファイルの生成
#
cfg1_out.c cfg1_out.db: cfg1_out.timestamp ;
cfg1_out.timestamp: $(APPL_CFG) $(TECSGEN_TIMESTAMP)
	$(CFG) --pass 1 $(CFG_KERNEL) $(patsubst -include=%,-I%,$(INCLUDES)) $(CFG_TABS) \
						-M $(DEPDIR)/cfg1_out_c.d $(TARGET_KERNEL_CFG) $<

$(CFG1_OUT): $(START_OBJS) cfg1_out.obj $(END_OBJS) $(HIDDEN_OBJS) \
													$(CFG1_OUT_LDSCRIPT)
	$(call linker,$(CFG1_OUT),$(START_OBJS) cfg1_out.obj $(LIBS) $(END_OBJS),$(CFLAGS),$(LDFLAGS) $(CFG1_OUT_LDFLAGS))

cfg1_out.syms: $(CFG1_OUT)
	$(call obj2syms,$(CFG1_OUT),cfg1_out.syms)

cfg1_out.srec: $(CFG1_OUT)
	$(call obj2srec,$(CFG1_OUT),cfg1_out.srec)

$(CFG2_OUT_SRCS) cfg2_out.db: kernel_cfg.timestamp ;
kernel_cfg.timestamp: cfg1_out.db cfg1_out.syms cfg1_out.srec
	$(CFG) --pass 2 $(CFG_KERNEL) $(patsubst -include=%,-I%,$(INCLUDES)) -T $(TARGET_KERNEL_TRB)

#
#  オフセットファイル（offset.h）の生成規則
#
$(OFFSET_H): offset.timestamp ;
offset.timestamp: cfg1_out.db cfg1_out.syms cfg1_out.srec
	$(CFG) --pass 2 -O $(CFG_KERNEL) $(patsubst -include=%,-I%,$(INCLUDES)) -T $(TARGET_OFFSET_TRB) \
				--rom-symbol cfg1_out.syms --rom-image cfg1_out.srec
# Remove unsupported C-style comments
	$(SED) -i '/\/\*/d' offset.h	

#
#  カーネルライブラリファイルの生成
#
libkernel.a: $(OFFSET_H) $(KERNEL_LIB_OBJS)
	rm -f libkernel.a
	$(call archive,libkernel.a,$(KERNEL_LIB_OBJS))

#
#  特別な依存関係の定義
#
svc_table.obj: omit_svc.h
tBannerMain.obj: $(filter-out tBannerMain.obj,$(ALL2_OBJS)) $(LIBS_DEP)

#
#  全体のリンク
#
$(OBJFILE): $(ALL_OBJS) $(LIBS_DEP) $(LDSCRIPT)
	$(call linker,$(OBJFILE),$(START_OBJS) $(APPL_OBJS) $(SYSSVC_OBJS) $(CFG_OBJS) $(ALL_LIBS) $(END_OBJS),$(CFLAGS),$(LDFLAGS) $(OBJ_LDFLAGS))
	$(CC_CONVERTER) $(OBJFILE) $(OBJNAME).x

#
#  シンボルファイルの生成
#
$(OBJNAME).syms: $(OBJFILE)
	$(call obj2syms,$(OBJFILE),$(OBJNAME).syms)

#
#  バイナリファイルの生成
#
$(OBJNAME).bin: $(OBJFILE)
	$(OBJCOPY) -O binary -S $(OBJFILE) $(OBJNAME).bin

#
#  Sレコードファイルの生成
#
$(OBJNAME).srec: $(OBJFILE)
	$(call obj2srec,$(OBJFILE),$(OBJNAME).srec)

#
#  エラーチェック処理
#
.PHONY: check
check: check.timestamp ;
check.timestamp: cfg2_out.db $(OBJNAME).syms $(OBJNAME).srec
	$(CFG) --pass 3 $(CFG_KERNEL) -O $(patsubst -include=%,-I%,$(INCLUDES)) -T $(TARGET_CHECK_TRB) \
				--rom-symbol $(OBJNAME).syms --rom-image $(OBJNAME).srec
	@echo "configuration check passed"

#
#  コンパイル結果の消去
#
.PHONY: clean
clean:
	rm -f \#* *~ *.obj $(DEPDIR)/*.d $(CLEAN_FILES) check.timestamp
	rm -f $(OBJFILE) $(OBJNAME).syms $(OBJNAME).srec $(OBJNAME).bin
	rm -f kernel_cfg.timestamp $(CFG2_OUT_SRCS) cfg2_out.db
	rm -f offset.timestamp $(OFFSET_H)
	rm -f cfg1_out.syms cfg1_out.srec $(CFG1_OUT)
	rm -f cfg1_out.timestamp cfg1_out.c cfg1_out.db
	rm -rf $(TECSGENDIR)
ifndef KERNEL_LIB
	rm -f libkernel.a
endif
	rm -rf *.map
	rm -rf kernel_cfg_asm.src

.PHONY: cleankernel
cleankernel:
	rm -f $(OFFSET_H) $(KERNEL_LIB_OBJS)
	rm -f $(KERNEL_LIB_OBJS:%.obj=$(DEPDIR)/%.d)

.PHONY: realclean
realclean: clean
	rm -f $(REALCLEAN_FILES)

#
#  コンフィギュレータが生成したファイルのコンパイルルールの定義
#
#  コンフィギュレータが生成したファイルは，共通のコンパイルオプション
#  のみを付けてコンパイルする．
#
ALL_CFG_COBJS = $(CFG_COBJS) cfg1_out.obj
ALL_CFG_ASMOBJS = $(CFG_ASMOBJS)

$(ALL_CFG_COBJS): %.obj: %.c
	$(call compiler_cc,$<,$(CFLAGS) $(CFG_CFLAGS))

$(ALL_CFG_COBJS:.obj=.s): %.s: %.c
	$(CC) -S $(CFLAGS) $(CFG_CFLAGS) $<

$(ALL_CFG_ASMOBJS): %.obj: %.S
	$(CC) -c -MD -MP -MF $(DEPDIR)/$*.d $(CFLAGS) $(CFG_CFLAGS) $<

#
#  依存関係ファイルのインクルード
#
-include $(DEPDIR)/*.d

#
#  開発ツールのコマンド名の定義
#
ifeq ($(TOOL),gcc)
	#
	#  GNU開発環境用
	#
	ifdef GCC_TARGET
		GCC_TARGET_PREFIX = $(GCC_TARGET)-
	else
		GCC_TARGET_PREFIX =
	endif
	CC := $(GCC_TARGET_PREFIX)gcc
	CXX := $(GCC_TARGET_PREFIX)g++
	AS := $(GCC_TARGET_PREFIX)as
	LD := $(GCC_TARGET_PREFIX)ld
	AR := $(GCC_TARGET_PREFIX)ar
	NM := $(GCC_TARGET_PREFIX)nm
	RANLIB := $(GCC_TARGET_PREFIX)ranlib
	OBJCOPY := $(GCC_TARGET_PREFIX)objcopy
	OBJDUMP := $(GCC_TARGET_PREFIX)objdump
endif

ifdef DEVTOOLDIR
	CC := $(DEVTOOLDIR)/$(CC)
	CXX := $(DEVTOOLDIR)/$(CXX)
	AS := $(DEVTOOLDIR)/$(AS)
	LD := $(DEVTOOLDIR)/$(LD)
	AR := $(DEVTOOLDIR)/$(AR)
	NM := $(DEVTOOLDIR)/$(NM)
	RANLIB := $(DEVTOOLDIR)/$(RANLIB)
	OBJCOPY := $(DEVTOOLDIR)/$(OBJCOPY)
	OBJDUMP := $(DEVTOOLDIR)/$(OBJDUMP)
endif

ifndef LINK
ifdef USE_CXX
	LINK = $(CXX)
else
	LINK = $(CC)
endif
endif

#
#  コンパイルルールの定義
#
$(KERNEL_COBJS): %.obj: %.c
	$(call compiler_cc,$<,$(CFLAGS) $(KERNEL_CFLAGS))

$(KERNEL_ASMOBJS): %.obj: %.src
	$(call compiler_as,$<,$(ASFLAGS) $(KERNEL_ASFLAGS))

$(SYSSVC_COBJS): %.obj: %.c
	$(call compiler_cc,$<,$(CFLAGS) $(SYSSVC_CFLAGS))

$(SYSSVC_ASMOBJS): %.obj: %.src
	$(call compiler_as,$<,$(ASFLAGS) $(SYSSVC_ASFLAGS))

$(APPL_COBJS): %.obj: %.c
	$(call compiler_cc,$<,$(CFLAGS) $(APPL_CFLAGS))

$(APPL_ASMOBJS): %.obj: %.src
	$(call compiler_as,$<,$(ASFLAGS) $(APPL_ASFLAGS))
