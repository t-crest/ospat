
CFLAGS	=	$(CONFIG_CFLAGS) -DPOK_ARCH_PATMOS -iwithprefix include -target patmos-unknown-unknown-elf $(KIND_CFLAGS) #$(GENERIC_FLAGS) -Wall -g -O0 -Wuninitialized -Xopt -disable-internalize

LDFLAGS	= 	-target patmos-unknown-unknown-elf