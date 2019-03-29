
###########################################################
# GCC template makefile
###########################################################
CPU_SOURCES = main.c
CPU_SOURCES += debug.c
CPU_SOURCES += Hw_Config.c
CPU_SOURCES += Hw_Led.c
CPU_SOURCES += lib_dbg.c
CPU_SOURCES += Private_Mode.c
CPU_SOURCES += stm32f10x_it.c
CPU_SOURCES += syscalls.c


C_SOURCES += $(CPU_SOURCES)