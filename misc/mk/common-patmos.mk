
CFLAGS	=	$(CONFIG_CFLAGS) -DPOK_ARCH_PATMOS -iwithprefix include -target patmos-unknown-unknown-elf $(KIND_CFLAGS) $(GENERIC_FLAGS) -Wall -g -O0 -Wuninitialized

LDFLAGS	= 	-target patmos-unknown-unknown-elf \
			#-nostartfiles \
			#-Wl,-internalize-public-api-list=pok_update_tick \
			#-Wl,-internalize-public-api-list=pok_current_partition \
			#-Wl,-internalize-public-api-list=pok_partitions \
			#-Wl,-internalize-public-api-list=current_thread \
			#-Wl,-internalize-public-api-list=pok_core_syscall \
			#-Wl,-internalize-public-api-list=pok_arch_decr_int \
			#-Wl,-internalize-public-api-list=current_context \
			#-Wl,-internalize-public-api-list=context_switch \
			#-Wl,-internalize-public-api-list=pok_arch_sc_int \
			#-Wl,-internalize-public-api-list=pok_boot
			#-m $(ELF_MODE)
