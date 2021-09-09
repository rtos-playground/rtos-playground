CC = arm-none-eabi-gcc
BIN := FreeRTOS.elf

BUILD_DIR := build

FREERTOS_DIR := /FreeRTOS/FreeRTOS
KERNEL_DIR := $(FREERTOS_DIR)/Source

FREERTOS_PLUS_DIR := /FreeRTOS/FreeRTOS-Plus

SOURCE_FILES += startup.c main.c

SOURCE_FILES += $(KERNEL_DIR)/portable/GCC/ARM_CM3/port.c
SOURCE_FILES += $(KERNEL_DIR)/tasks.c
SOURCE_FILES += $(KERNEL_DIR)/list.c
SOURCE_FILES += $(KERNEL_DIR)/queue.c
SOURCE_FILES += $(KERNEL_DIR)/timers.c
SOURCE_FILES += $(KERNEL_DIR)/event_groups.c
SOURCE_FILES += ${KERNEL_DIR}/portable/MemMang/heap_4.c

INCLUDE_DIRS += -I.
INCLUDE_DIRS += -I$(KERNEL_DIR)/include
INCLUDE_DIRS += -I$(KERNEL_DIR)/portable/GCC/ARM_CM3
INCLUDE_DIRS += -I$(FREERTOS_DIR)/Demo/Common/drivers/LuminaryMicro/

    SOURCE_FILES += $(KERNEL_DIR)/stream_buffer.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/AbortDelay.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/BlockQ.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/blocktim.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/countsem.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/death.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/dynamic.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/EventGroupsDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/flop.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/GenQTest.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/integer.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/IntSemTest.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/MessageBufferAMP.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/MessageBufferDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/PollQ.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QPeek.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QueueOverwrite.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QueueSet.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/QueueSetPolling.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/recmutex.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/semtest.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/StaticAllocation.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/StreamBufferDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/StreamBufferInterrupt.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/TaskNotify.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Minimal/TimerDemo.c
    SOURCE_FILES += ${FREERTOS_DIR}/Demo/Common/Full/print.c

    INCLUDE_DIRS += -I$(FREERTOS_DIR)/Demo/Common/include
    INCLUDE_DIRS += -I${FREERTOS_PLUS_DIR}/Source/FreeRTOS-Plus-Trace/Include/

DEFINES :=  -DQEMU_SOC_MPS2 -DHEAP4

LDFLAGS = -T standalone.ld -specs=nano.specs --specs=rdimon.specs -lc -lrdimon
LDFLAGS += -Xlinker -Map=${BUILD_DIR}/output.map
LDFLAGS += -Wl,--gc-sections

CFLAGS += -nostartfiles -mthumb -mcpu=cortex-m3 -Wno-error=implicit-function-declaration
CFLAGS += -Wno-builtin-declaration-mismatch -Werror

CFLAGS += -ggdb3 -Og

CFLAGS += -fstrict-aliasing -Wstrict-aliasing -Wno-error=address-of-packed-member

OBJ_FILES := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

CPPFLAGS += $(DEFINES)
CFLAGS += $(INCLUDE_DIRS)

.PHONY: clean

$(BUILD_DIR)/$(BIN) : $(OBJ_FILES)
	$(CC) -ffunction-sections -fdata-sections $(CFLAGS) $(LDFLAGS) $+ -o $(@) ${FREERTOS_DIR}/Demo/Common/drivers/LuminaryMicro/arm-none-eabi-gcc/libdriver.a

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

INCLUDES := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.d)
-include $(INCLUDES)

${BUILD_DIR}/%.o : %.c Makefile
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	-rm -rf build

