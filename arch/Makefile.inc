
###########################################################
# GCC template makefile
###########################################################

SUB_ARCH := \
CMSIS/Core/CM3 \
CMSIS/Core/CM3/startup/gcc \
STM32F10x_StdPeriph_Driver/Src 

ifeq ($(COMMAND),)
SUB_ARCH += Src 
else ifeq ($(COMMAND), lib_debug)
SUB_ARCH += lib_debug/Src
else ifeq ($(COMMAND), uart)
SUB_ARCH += uart_study/Src
else ifeq ($(COMMAND), jtag)
SUB_ARCH += jtag_remap/Src
else ifeq ($(COMMAND), usb)
SUB_ARCH += USB/Src
else 

endif
ifeq ($(MANGO_Z1),y)
#SUB_ARCH += cc2520/Src 
endif

SUB_ARCH := $(addprefix $(TOP)/arch/, $(SUB_ARCH))

vpath %.c $(SUB_ARCH)
vpath %.s $(SUB_ARCH)

sinclude $(addsuffix /Makefile.inc, $(SUB_ARCH))

EXTRAINCDIRS += \
$(TOP)/arch/CMSIS/Core/CM3 \
$(TOP)/arch/STM32F10x_StdPeriph_Driver/Inc 


#$(TOP)/arch/STM32_USB-FS-Device_Driver/Inc 

ifeq ($(COMMAND),)
EXTRAINCDIRS += $(TOP)/arch/Inc 
else ifeq ($(COMMAND), lib_debug)
EXTRAINCDIRS += $(TOP)/arch/lib_debug/Inc
else ifeq ($(COMMAND), uart)
EXTRAINCDIRS += $(TOP)/arch/uart_study/Inc
else ifeq ($(COMMAND), usb)
EXTRAINCDIRS += $(TOP)/arch/USB/Inc
else ifeq ($(COMMAND), jtag)
EXTRAINCDIRS += $(TOP)/jtag_remap/Inc
else

endif



ifeq ($(MANGO_Z1),y)

#EXTRAINCDIRS += $(TOP)/arch/cc2520/Inc \

endif