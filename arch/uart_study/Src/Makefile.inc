
###########################################################
# GCC template makefile
###########################################################

USART_MAINSOURCES = 
USART_MAINSOURCES += debug.c
USART_MAINSOURCES += Hw_Config.c
USART_MAINSOURCES += led.c
USART_MAINSOURCES += lib_dbg.c
USART_MAINSOURCES += main.c
USART_MAINSOURCES += Private_Mode.c
USART_MAINSOURCES += stm32f10x_it.c
USART_MAINSOURCES += syscalls.c


$(C_SOURCES) += $(USART_MAINSOURCES)
