TOPDIR=		../../../

include $(TOPDIR)/misc/mk/config.mk
-include $(TOPDIR)/misc/mk/common-$(ARCH).mk

LO_TARGET=	string.lo

LO_OBJS=	memcpy.o \
		memset.o \
		memcmp.o \
		strcmp.o \
		strcpy.o \
		streq.o \
		strlen.o
#itoa.o \


# XXX: Compile arch optimized versions
LO_DEPS=

all: $(LO_TARGET)


.PHONY: clean distclean depend all

clean:
	$(RM) $(LO_TARGET)
	$(RM) $(LO_OBJS)

distclean:
	$(RM) $(LO_TARGET)
	$(RM) $(LO_OBJS)
	$(RM) .depend.mk

depend:
	$(if $(LO_OBJS), $(CC) $(CFLAGS) -MM $(wildcard *.c) $(wildcard *.S) > .depend.mk,)

include $(TOPDIR)/misc/mk/rules-common.mk
include $(TOPDIR)/misc/mk/rules-partition.mk
