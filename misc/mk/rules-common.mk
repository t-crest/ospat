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
LDFLAGS	= 	-Wl,-internalize-public-api-list=pok_update_tick \
			-Wl,-internalize-public-api-list=pok_current_partition \
			-Wl,-internalize-public-api-list=pok_partitions \
			-Wl,-internalize-public-api-list=current_thread \
			-Wl,-internalize-public-api-list=pok_core_syscall \
			-Wl,-internalize-public-api-list=pok_arch_decr_int \
			-Wl,-internalize-public-api-list=pok_current_context \
			-Wl,-internalize-public-api-list=context_switch \
			-Wl,-internalize-public-api-list=pok_arch_sc_int \
			-Wl,-internalize-public-api-list=pok_boot \
			-Wl,-internalize-public-api-list=pok_sched \
			-Wl,-internalize-public-api-list=pok_tick_counter \
			-Wl,-internalize-public-api-list=pok_arch_preempt_enable \
			-Wl,-internalize-public-api-list=pok_bsp_time_init \
			-Wl,-internalize-public-api-list=pok_context_create \
			-Wl,-internalize-public-api-list=pok_arch_idle \
			-Wl,-internalize-public-api-list=pok_create_space \
			-Wl,-internalize-public-api-list=pok_bsp_mem_alloc \
			-Wl,-internalize-public-api-list=pok_arch_init \
			-Wl,-internalize-public-api-list=pok_arch_set_decr \
			-Wl,-internalize-public-api-list=next_timer \
			-Wl,-internalize-public-api-list=time_inter \
			-Wl,-internalize-public-api-list=get_patmos_tb \
			-Wl,-internalize-public-api-list=pok_space_context_create \
			-Wl,-internalize-public-api-list=pok_thread_stack_addr\
			-Wl,-internalize-public-api-list=pok_thread_shadow_stack_addr\
			-Wl,-internalize-public-api-list=pok_cons_write \
			-Wl,-internalize-public-api-list=restore_context \
			-Wl,-internalize-public-api-list=pok_thread_start_execution \
			-Wl,-internalize-public-api-list=pok_sched_end_period 
endif

ifneq ($(XCOV),) 
CFLAGS+=-DPOK_NEEDS_COVERAGE_INFOS
endif

ifneq ($(POK_CONFIG_OPTIMIZE_FOR_GENERATED_CODE),) 
CFLAGS+=-DPOK_CONFIG_OPTIMIZE_FOR_GENERATED_CODE=1
endif

$(LO_TARGET): $(LO_DEPS) $(LO_OBJS)
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[LD] $@ "
	$(LD) -fpatmos-link-object -fpatmos-emit-object $(LDFLAGS) $(LDOPTS) $(LO_DEPS) $(LO_OBJS) -o $(LO_TARGET)
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi

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
