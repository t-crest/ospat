ECHO_FLAGS_ONELINE=-n

AR=$(AR_$(ARCH))
CC=$(CC_$(ARCH))
CXX=$(CXX_$(ARCH))
LD=$(LD_$(ARCH))
OBJCOPY=$(OBJCOPY_$(ARCH))
OBJDUMP=$(OBJDUMP_$(ARCH))
QEMU=$(QEMU_$(ARCH))
CONFIG_QEMU=$(CONFIG_QEMU_$(ARCH))
RANLIB=$(RANLIB_$(ARCH))
GNATMAKE=$(GNATMAKE_$(ARCH))

CFLAGS+=-D__POK_C__

# Clang compiler deletes unreferenced symbols during compilation
# -Wl,-internalize-public-api-list tells the compiler not to delete symbols
# TODO: try to use __attribute__((used)) to mark functions and variables

ifeq ($(ARCH), patmos)
# LDFLAGS	= 	-Xopt -internalize-public-api-list=pok_update_tick \
# 			-Xopt -internalize-public-api-list=pok_current_partition \
# 			-Xopt -internalize-public-api-list=pok_partitions \
# 			-Xopt -internalize-public-api-list=current_thread \
# 			-Xopt -internalize-public-api-list=pok_core_syscall \
# 			-Xopt -internalize-public-api-list=pok_arch_decr_int \
# 			-Xopt -internalize-public-api-list=pok_current_context \
# 			-Xopt -internalize-public-api-list=context_switch \
# 			-Xopt -internalize-public-api-list=pok_arch_sc_int \
# 			-Xopt -internalize-public-api-list=pok_boot \
# 			-Xopt -internalize-public-api-list=pok_sched \
# 			-Xopt -internalize-public-api-list=pok_tick_counter \
# 			-Xopt -internalize-public-api-list=pok_arch_preempt_enable \
# 			-Xopt -internalize-public-api-list=pok_bsp_time_init \
# 			-Xopt -internalize-public-api-list=pok_context_create \
# 			-Xopt -internalize-public-api-list=pok_arch_idle \
# 			-Xopt -internalize-public-api-list=pok_create_space \
# 			-Xopt -internalize-public-api-list=pok_bsp_mem_alloc \
# 			-Xopt -internalize-public-api-list=pok_arch_init \
# 			-Xopt -internalize-public-api-list=pok_arch_set_decr \
# 			-Xopt -internalize-public-api-list=next_timer \
# 			-Xopt -internalize-public-api-list=time_inter \
# 			-Xopt -internalize-public-api-list=get_patmos_tb \
# 			-Xopt -internalize-public-api-list=pok_space_context_create \
# 			-Xopt -internalize-public-api-list=pok_thread_stack_addr\
# 			-Xopt -internalize-public-api-list=pok_thread_shadow_stack_addr\
# 			-Xopt -internalize-public-api-list=pok_cons_write \
# 			-Xopt -internalize-public-api-list=restore_context \
# 			-Xopt -internalize-public-api-list=pok_thread_start_execution \
# 			-Xopt -internalize-public-api-list=pok_sched_end_period \
# 			-Xopt -internalize-public-api-list=_interval_ISR \
# 			-Xopt -internalize-public-api-list=SET_PARTITION_MODE
endif

ifneq ($(XCOV),) 
CFLAGS+=-DPOK_NEEDS_COVERAGE_INFOS
endif

ifneq ($(POK_CONFIG_OPTIMIZE_FOR_GENERATED_CODE),) 
CFLAGS+=-DPOK_CONFIG_OPTIMIZE_FOR_GENERATED_CODE=1
endif

ifeq ($(ARCH), patmos)
$(LO_TARGET): $(LO_DEPS) $(LO_OBJS)
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[LD] $@ "
	$(LD) -fpatmos-link-object -fpatmos-emit-object $(LDFLAGS) $(LDOPTS) $(LO_DEPS) $(LO_OBJS) -o $(LO_TARGET)
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi



endif

%.a: $(LO_DEPS)
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[AR] $@ "
	$(AR) $@ $(LO_DEPS)
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi

%.o: %.S
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[CC] $< "
	$(CC) -c $(CFLAGS) -DASM_SOURCE=1 $< -o $@
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi

%.o: %.s
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[CC] $< "
	$(CC) -c $< -o $@
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi

%.o: %.c
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[CC] $< "
	$(CC) -c $(CFLAGS) $(COPTS) $< -o $@
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK"; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi

%.o: %.adb %.ads
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[ADA] $< "
	$(CC) -c $(ADAFLAGS) $< -o $@
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK"; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi

$(POK_PATH)/misc/mk/config.mk:
	cd $(POK_PATH) && $(MAKE) configure

-include .depend.mk

common-clean:
	$(RM) *~ .depend.mk
	$(RM) $(TARGET) $(LO_TARGET) $(LO_DEPS) $(LO_OBJS) $(OBJS) floppy.img partitions.lst partitions.cpio partitions.bin sizes.o sizes.c cpio.o *.elf.map



ifneq ($(CC),)
check-compiler:
	true
else
check-compiler:
	@echo "";
	@echo "Aieeeee, you don't have the compiler for $(ARCH)"
	@echo "-----------------------------------------------";
	@echo "";
	@echo "Please read the POK user guide and come back here !"
	@echo "";
	false
endif
