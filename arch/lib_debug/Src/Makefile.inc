
###########################################################
# GCC template makefile
###########################################################


LIB_DEDBG = \
LIB_DEDBG += debug.c 
LIB_DEDBG += hw_config.c
LIB_DEDBG += lib_dbg.c
LIB_DEDBG += main.c
LIB_DEDBG += stm32f10x_conf.c
LIB_DEDBG += stm32f10x_it.c

$(C_SOURCES) += $(LIB_DEDBG)