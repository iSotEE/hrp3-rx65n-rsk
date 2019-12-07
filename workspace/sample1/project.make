APPLDIRS += $(SRCDIR)/sample
APPL_COBJS := sample1.obj

#
# iSotEE
#
include $(RENESAS_FIT_DIR)/Makefile.FIT
include $(ISOTEE_DIR)/target/rx65n/hrp3/host/Makefile.host
include $(THREAD_METRIC_DIR)/tm_porting_layer_hrp3.Makefile
