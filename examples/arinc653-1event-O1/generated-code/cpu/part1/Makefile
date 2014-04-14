export DEPLOYMENT_HEADER=$(shell pwd)/deployment.h
include $(POK_PATH)/misc/mk/config.mk
TARGET = part1.elf
OBJS = main.o activity.o deployment.o
ifneq ($(ARCH), patmos)
LINKERSCRIPT = partition_1.lds
endif
all: print libpok $(TARGET)

print:	
	$(ECHO) $(ECHO_FLAGS) "[Start compiling partition $(TARGET)] "
clean: common-clean
include $(POK_PATH)/misc/mk/common-$(ARCH).mk
include $(POK_PATH)/misc/mk/rules-partition.mk
include $(POK_PATH)/misc/mk/rules-common.mk