
ifeq ($(USE_FREERTOS),y)


SUB_ARCH := \
freeRTOS/Common/Minimal \
freeRTOS/MemMang \
freeRTOS/portable/ARM_CM3 \


SUB_ARCH  := $(addprefix $(TOP)/kernel/, $(SUB_ARCH))

vpath %.c $(SUB_ARCH)
vpath %.s $(SUB_ARCH)

sinclude $(addsuffix /Makefile.inc, $(SUB_ARCH))

EXTRAINCDIRS += \
$(TOP)/kernel/freeRTOS/include \
$(TOP)/kernel/freeRTOS/portable/ARM_CM3 \

endif
