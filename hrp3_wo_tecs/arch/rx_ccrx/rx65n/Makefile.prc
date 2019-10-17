#
#		Makefile のプロセッサ依存部（RX64M用）
#

#
#  プロセッサ依存部ディレクトリ名の定義
#
PRCDIR = $(SRCDIR)/arch/$(CORE)_$(TOOL)/$(PRC)

#
#  コンパイルオプション
#
INCLUDES += -include=$(PRCDIR)
COPTS += -isa=rxv2
ASFLAGS += -isa=rxv2

#
#  カーネルに関する定義
#
KERNEL_DIRS += $(PRCDIR)
KERNEL_COBJS += prc_timer.obj prc_kernel_impl.obj
KERNEL_ASMOBJS += start.obj
SYSSVC_COBJS += prc_serial.obj

#
#  コンフィギュレータ関係の変数の定義
#
CFG_TABS := $(CFG_TABS) --symval-table $(PRCDIR)/prc_sym.def

#
#  コア依存部
#
include $(SRCDIR)/arch/$(CORE)_$(TOOL)/common/Makefile.core
