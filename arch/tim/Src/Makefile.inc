
###########################################################
# GCC template makefile
###########################################################


TIM_SOURCES = debug.c 
TIM_SOURCES += Hw_Config.c
TIM_SOURCES += led.c
TIM_SOURCES += lib_dbg.c
TIM_SOURCES += main.c
TIM_SOURCES += Private_Mode.c
TIM_SOURCES += stm32f10x_it.c
TIM_SOURCES += syscalls.c

C_SOURCES += $(TIM_SOURCES)