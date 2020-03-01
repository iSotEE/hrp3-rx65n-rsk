APPLDIRS += 
APPL_COBJS := project.obj

include $(THREAD_METRIC_DIR)/tm_porting_layer_hrp3.make

#
# iSotEE
#
include $(RENESAS_FIT_DIR)/Makefile.FIT
include $(ISOTEE_DIR)/target/rx65n/hrp3/host/Makefile.host
