ifeq ($(TOPDIR),)
CFLAGS += -I$(POK_PATH)/libpok/include -I.
else
CFLAGS += -I$(TOPDIR)/libpok/include -I.
endif

ifneq ($(LUSTRE_DIRECTORY),)
CFLAGS += -I$(LUSTRE_DIRECTORY)
endif

ifneq ($(DEPLOYMENT_HEADER),)
COPTS += -include $(DEPLOYMENT_HEADER)
endif

libpok: 
	$(CD) $(POK_PATH)/libpok && $(MAKE) distclean all

ifeq ($(ARCH), patmos)
# PWD is the partition subdir
# $(@D)/partition_
$(TARGET): $(OBJS)
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[Assemble partition $@ "
	$(LD) $(LDFLAGS) -o $@ $+ $(POK_PATH)/libpok/libpok.lo
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK]"; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO]"; fi
else
# PWD is the partition subdir
# $(@D)/partition_
$(TARGET): $(OBJS)
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[Assemble partition $@ "
	$(LD) $(LDFLAGS) --nostdlib --cref -T $(LINKERSCRIPT) -o $@ --whole-archive $+ -L$(POK_PATH)/libpok -lpok  -z muldefs -Map $@.map
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi
	# SKIP LOADER
	powerpc-elf-strip $@

endif

libpok-clean:
	$(CD) $(POK_PATH)/libpok && $(MAKE) clean
