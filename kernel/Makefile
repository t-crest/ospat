include ../misc/mk/config.mk
-include ../misc/mk/common-$(ARCH).mk

LO_TARGET=pok.lo

ifeq ($(ARCH), patmos)
LO_DEPS=core/core.lo \
		arch/arch.lo \
        middleware/middleware.lo \


        
else
LO_DEPS=core/core.lo \
        middleware/middleware.lo \
        libc/libc.lo \
        arch/arch.lo
endif


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
all: check-compiler .depend $(LO_TARGET)
endif

arch/arch.lo::
	$(CD) arch && $(MAKE)

core/core.lo::
	$(CD) core && $(MAKE)

ifneq ($(ARCH), patmos)
core/core.lo::
	$(CD) libc && $(MAKE)
endif

middleware/middleware.lo::
	$(CD) middleware && $(MAKE)

.PHONY: all clean distclean depend

clean: common-clean
	$(CD) arch && $(MAKE) clean
	$(CD) core && $(MAKE) clean
ifneq ($(ARCH), patmos)
	$(CD) libc && $(MAKE) clean
endif
	$(CD) middleware && $(MAKE) clean
	$(RM) $(LO_TARGET)

distclean: clean
	$(CD) arch && $(MAKE) distclean
	$(CD) core && $(MAKE) distclean
ifneq ($(ARCH), patmos)
	$(CD) libc && $(MAKE) distclean
endif
	$(CD) middleware && $(MAKE) distclean
	$(RM) .depend

depend .depend:
	$(CD) arch && $(MAKE) depend
	$(CD) core && $(MAKE) depend
ifneq ($(ARCH), patmos)
	$(CD) libc && $(MAKE) depend
endif
	$(CD) middleware && $(MAKE) depend
	$(TOUCH) .depend

include ../misc/mk/rules-common.mk
include ../misc/mk/rules-kernel.mk
