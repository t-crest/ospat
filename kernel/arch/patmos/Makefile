TOPDIR=		../../../

include $(TOPDIR)/misc/mk/config.mk
-include $(TOPDIR)/misc/mk/common-$(ARCH).mk

LO_TARGET=	patmos.lo

LO_OBJS= timer.o \
		thread.o \
		space.o \
		syscalls.o \
		arch.o

LO_DEPS=	$(BSP)/$(BSP).lo

all: $(LO_TARGET) entry.o cswitch.o

$(BSP)/$(BSP).lo::
	$(CD) $(BSP) && $(MAKE)

.PHONY: clean distclean depend all

clean: common-clean
	$(MAKE) -C prep $@
ifdef BSP
	$(CD) $(BSP) && $(MAKE) clean
endif

distclean: clean
	$(MAKE) -C prep $@
	$(RM) .depend.mk
ifdef BSP
	$(CD) $(BSP) && $(MAKE) distclean
endif

depend:
	$(if $(LO_OBJS), $(CC) $(CFLAGS) -MM $(wildcard *.c) $(wildcard *.S) > .depend.mk,)
ifdef BSP
	$(CD) $(BSP) && $(MAKE) depend
endif

include $(TOPDIR)/misc/mk/rules-common.mk
include $(TOPDIR)/misc/mk/rules-kernel.mk

