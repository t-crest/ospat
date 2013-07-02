-include .depend.mk

DD=/bin/dd

ifeq ($(ARCH),patmos) 

$(TARGET):
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[ELF] Building kernel.elf "
	$(LD) -nostartfiles $(LDFLAGS) -Xgold -T -Xgold $(POK_PATH)/misc/ldscripts/$(ARCH)/$(BSP)/kernel.lds -f $(LDOPTS) -o $@ $(POK_PATH)/kernel/pok.lo $(OBJS)
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi 

else

LDOPTS=-T $(POK_PATH)/misc/ldscripts/$(ARCH)/$(BSP)/kernel.lds -o $@ $(POK_PATH)/kernel/pok.lo 

assemble-partitions:
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[BIN] partitions.bin"
	# padding to get aligned file size (needed for SPARC)
	for v in $(PARTITIONS); do \
		$(DD) if=/dev/zero of=$$v oflag=append conv=notrunc bs=1 count=`echo "4 - (\`ls -l $$v | awk '{print $$5}'\` % 4)" | bc`;\
	done
	cat $(PARTITIONS) > partitions.bin
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi


$(TARGET): assemble-partitions
#	$(RM) -f cpio.c
#	$(TOUCH) cpio.c
#	$(CC) $(CONFIG_CFLAGS) -c cpio.c -o cpio.o
#	$(RM) -f cpio.c
#	$(OBJCOPY) --add-section .archive=$(ARCHIVE) cpio.o
	$(RM) -f sizes.c
	$(TOUCH) sizes.c
	$(ECHO) "#include <types.h>" >> sizes.c
	$(ECHO) "uint32_t part_sizes[] = {" >> sizes.c
	N=1 ; for v in $(PARTITIONS); do \
		if test $$N -eq 0; then $(ECHO) "," >> sizes.c ; fi ; N=0 ;\
		ls -l $$v|awk '{print $$5}' >> sizes.c ; \
	done
	$(ECHO) "};" >> sizes.c
	$(CC) -DPOK_ARCH_PATMOS $(CONFIG_CFLAGS) -I $(POK_PATH)/kernel/include -c sizes.c -o sizes.o
	$(OBJCOPY) --add-section .archive2=partitions.bin sizes.o
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[LD] $@"
	$(ECHO) "$(LD) $(LDFLAGS) -T `pwd`/kernel/kernel.lds -o -L`pwd`/part1 -L`pwd`/part2 $@ $(KERNEL) $(OBJS) sizes.o -Map $@.map"
	$(LD) $(LDFLAGS) -T `pwd`/kernel/kernel.lds -o $@ $(KERNEL) $(OBJS) sizes.o -L`pwd`/part1 -L`pwd`/part2 -Map $@.map

	#$(LD) $(LDFLAGS) -T `pwd`/kernel/kernel.lds -o $@ $(KERNEL) $(OBJS) sizes.o -L`pwd`/part1 -L`pwd`/part2 -Map $@.map
	#$(LD) $(LDFLAGS) -T $(POK_PATH)/misc/ldscripts/$(ARCH)/$(BSP)/kernel.lds -o $@ $(KERNEL) $(OBJS) sizes.o -Map $@.map
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi
endif

plop: assemble-partitions
	$(RM) -f sizes.c
	$(TOUCH) sizes.c
	$(ECHO) "#include <types.h>" >> sizes.c
	$(ECHO) "uint32_t part_sizes[] = {" >> sizes.c
	N=1 ; for v in $(PARTITIONS); do \
		if test $$N -eq 0; then $(ECHO) "," >> sizes.c ; fi ; N=0 ;\
		ls -l $$v|awk '{print $$5}' >> sizes.c ; \
	done
	$(ECHO) "};" >> sizes.c
	$(CC) $(CONFIG_CFLAGS) -I $(POK_PATH)/kernel/include -c sizes.c -o sizes.o
	$(OBJCOPY) --add-section .archive2=partitions.bin sizes.o
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[LD] $@"
	#$(LD) $(LDFLAGS) -T $(POK_PATH)/misc/ldscripts/$(ARCH)/$(BSP)/kernel.lds -o pok.elf $(KERNEL) $(OBJS) sizes.o -Map $@.map
	$(LD) $(LDFLAGS) -T `pwd`/kernel/kernel.lds -o pok.elf $(KERNEL) $(OBJS) sizes.o -Map $@.map
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi
