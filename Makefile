# "$@" 또는 "$(@)"는 바로 Target
# "$^"는 Depend 전체를 의미
#"$<"는 열거된 Depend중에 가장 왼쪽에 기술된 1개의 Depend

TOP = .

include $(TOP)/inc.mk

TARGET = wifiTest

USE_FREERTOS = y


#List C sources files here.
SRCS += $(C_SOURCES)

#List C++ sources files here.
CPPSRCS = 

#List Assmbler sources files here.
ASM_SOURCES = 

SUB_DIRS := 
SUB_DIRS += arch
SUB_DIRS += kernel

ifeq ($(USE_FREERTOS), y)
SUB_DIRS += kernel/freeRTOS
endif

ifeq ($(USE_FREERTOS), y)
CDEFS += -D FREE_RTOS
endif

SUB_DIRS := $(addprefix $(TOP)/,$(SUB_DIRS))

vpath %.c $(SUB_DIRS)
vpath %.s $(SUB_DIRS)

#include all sub directories makefile
sinclude $(addsuffix /Makefile.inc,$(SUB_DIRS))

# List of include file path
#     Each directory must be seperated by a space.
EXTRA_LIBDIRS = 

#LIBC_LIB = -L $(shell dirname `$(CC) $(ALL_CFLAGS) -print-file-name=libc.a`) -lc
#MATH_LIB = -L $(shell dirname `$(CC) $(ALL_CFLAGS) -print-file-name=libm.a`) -lm
#LIBGCC_LIB += -L $(shell dirname `$(CC) $(ALL_CFLAGS) -print-libgcc-file-name`) -lgcc
# CPLUSPLUS_LIB = -lstdc++

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
#LDFLAGS = -Map=$(TARGET).map --cref
LDSCRIPT = STM32F103RBTx_FLASH.ld
LD_LIBS = -lc -lm -lnosys -specs=nano.specs -u _printf_float -u _scanf_float -static
LDFLAGS = $(MCU) $(LD_LIBS) -Wl,-Map=$(TARGET).map,--cref -Wl,--gc-sections

LDFLAGS += $(patsubst %,-L%, $(EXTRA_LIBDIRS))
LDFLAGS += $(patsubst %,-L%, $(EXTRA_LIBS))

ifeq ($(ROM_MODE), y)
LDFLAGS += -TSTM32F103RBTx_ROM.ld
else
LDFLAGS += -TSTM32F103RBTx_FLASH.ld
endif

all: gccversion createdirs build sizeinfo

download: clean all
	~/stm32ld /dev/tty.usbserial-142401 115200 $(TARGET).bin

ifeq ($(FORMAT),ihex)
build: elf hex lss sym
hex: $(TARGET).hex
IMGEXT=hex
else
ifeq ($(FORMAT),binary)
build: elf bin lss sym
lss: $(TARGET).lss
bin: $(TARGET).bin
sym: $(TARGET).sym
IMGEXwT=bin
else
$(error "please check output-format $(FORMAT)")
endif
endif

doc:
	doxygen doc.mk

.PHONY: all build bin doc

include $(TOP)/rule.mk