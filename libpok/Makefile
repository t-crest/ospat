include ../misc/mk/config.mk
-include ../misc/mk/common-$(ARCH).mk

ifeq ($(ARCH), patmos)
LO_DEPS=	arch/arch.lo \
			core/core.lo \
			middleware/middleware.lo \
			arinc653/arinc653.lo
else
LO_DEPS=	arch/arch.lo \
			core/core.lo \
			middleware/middleware.lo \
			arinc653/arinc653.lo \
			libc/libc.lo
endif
#			drivers/drivers.lo \


ifeq ($(strip $(ARCH)), )
all:
	@echo "";
	@echo "Aieeeee, you forgot to provide an ARCH variable"
	@echo "-----------------------------------------------";
	@echo "";
	@echo "Please note that pok Makefile build must be run from code generation directory."
	@echo "";
	@exit 0
else
all: .depend libpok.lo
endif

libpok.lo: $(LO_DEPS)
	$(ECHO) $(ECHO_FLAGS) $(ECHO_FLAGS_ONELINE) "[LD] $@ "
	$(LD) $(LO_DEPS) $(LO_OBJS) -o libpok.lo
	if test $$? -eq 0; then $(ECHO) $(ECHO_FLAGS) $(ECHO_GREEN) " OK "; else $(ECHO) $(ECHO_FLAGS) $(ECHO_RED) " KO"; fi

arch/arch.lo::
	$(CD) arch && $(MAKE)

core/core.lo::
	$(CD) core && $(MAKE)

middleware/middleware.lo::
	$(CD) middleware && $(MAKE)

arinc653/arinc653.lo::
	$(CD) arinc653 && $(MAKE)

ifneq ($(ARCH), patmos)
libc/libc.lo::
	$(CD) libc && $(MAKE)
endif

#libm/libm.lo::
#	$(CD) libm && $(MAKE)

#drivers/drivers.lo::
#	$(CD) drivers && $(MAKE)

#protocols/protocols.lo::
#	$(CD) protocols && $(MAKE)

.PHONY: all clean distclean depend

clean: common-clean
	$(CD) arch && $(MAKE) clean
	$(CD) core && $(MAKE) clean
#	$(CD) drivers && $(MAKE) clean
ifneq ($(ARCH), patmos)
	$(CD) libc && $(MAKE) clean
endif
	$(CD) middleware && $(MAKE) clean
	$(CD) arinc653 && $(MAKE) clean
	$(RM) $(LO_TARGET)

distclean:
	$(CD) arch && $(MAKE) distclean
	$(CD) core && $(MAKE) distclean
#	$(CD) drivers && $(MAKE) distclean
ifneq ($(ARCH), patmos)
	$(CD) libc && $(MAKE) distclean
endif
	$(CD) middleware && $(MAKE) distclean
	$(CD) arinc653 && $(MAKE) distclean
	$(RM) libpok.a
	$(RM) .depend

depend .depend:
	$(CD) core && $(MAKE) depend
ifneq ($(ARCH), patmos)
	$(CD) libc && $(MAKE) depend
endif
#	$(CD) drivers && $(MAKE) depend
	$(CD) middleware && $(MAKE) depend
	$(CD) arinc653 && $(MAKE) depend
	$(TOUCH) .depend

include ../misc/mk/rules-common.mk
include ../misc/mk/rules-partition.mk
