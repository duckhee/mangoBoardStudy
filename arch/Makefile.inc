
###########################################################
# GCC template makefile
###########################################################

SUB_ARCH := \
CMSIS/Core/CM3 \
CMSIS/Core/CM3/startup/gcc \
STM32F10x_StdPeriph_Driver/Src \
Src \

ifeq ($(ESP_USE),y)
SUB_ARCH += ESP/Src \

endif



ifeq ($(MANGO_Z1),y)
#SUB_ARCH += cc2520/Src \

endif

SUB_ARCH := $(addprefix $(TOP)/arch/, $(SUB_ARCH))

vpath %.c $(SUB_ARCH)
vpath %.s $(SUB_ARCH)

sinclude $(addsuffix /Makefile.inc, $(SUB_ARCH))

EXTRAINCDIRS += \
$(TOP)/arch/Inc \
$(TOP)/arch/CMSIS/Core/CM3 \
$(TOP)/arch/STM32F10x_StdPeriph_Driver/Inc \
$(TOP)/arch/Inc \

ifeq ($(ESP_USE),y)
EXTRAINCDIRS += $(TOP)/arch/ESP/Inc \

endif

ifeq ($(MANGO_Z1),y)
#EXTRAINCDIRS += $(TOP)/arch/cc2520/Inc \

endif