
###########################################################
# GCC template makefile
###########################################################

JTAG_REMAP = 
JTAG_REMAP += debug.c
JTAG_REMAP += hw_config.c
JTAG_REMAP += key.c
JTAG_REMAP += led.c
JTAG_REMAP += main.c
JTAG_REMAP += seven_segment.c
JTAG_REMAP += stm32f10x_it.c

C_SOURCES += $(JTAG_REMAP)
