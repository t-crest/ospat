export DEPLOYMENT_HEADER=$(shell pwd)/deployment.h
include $(POK_PATH)/misc/mk/config.mk
ifneq ($(ARCH), patmos)
TARGET = part1.elf
else
TARGET = part1.lo
endif
OBJS = main.o activity.o deployment.o
ifneq ($(ARCH), patmos)
LINKERSCRIPT = partition_1.lds
endif
all: libpok $(TARGET)
clean: common-clean
include $(POK_PATH)/misc/mk/common-$(ARCH).mk
include $(POK_PATH)/misc/mk/rules-partition.mk
include $(POK_PATH)/misc/mk/rules-common.mk