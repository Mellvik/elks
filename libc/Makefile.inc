
VERSION=elks-0.3.0

INCLUDES=-I$(TOPDIR)/include -I$(TOPDIR)/libc/include -I$(TOPDIR)/elks/include
DEFINES=-D__LIBC__ -D__LIBC_VER__='"$(VERSION)"' -D__HAS_NO_FLOATS__

SDEFS=$(DEFINES)
CDEFS=$(DEFINES)

ARCH=-ffreestanding -fno-inline -melks -mcmodel=small -mno-segment-relocation-stuff -mtune=i8086

CC=ia16-elf-gcc
AS=ia16-elf-as
AR=ia16-elf-ar
LD=ia16-elf-ld

CFLAGS=$(ARCH) $(INCLUDES) $(CDEFS) -Wall -Os $(MULTILIB)
ASFLAGS=-mtune=i8086
LDFLAGS=-mtune=i8086
# This is used in subdirectories to quickly create a library archive without
# a symbol index
ARFLAGS_SUB=cqS

ifdef MULTISUBDIR
LIBC=$(TOPDIR)/libc/build-ml/$(MULTISUBDIR)/libc_elks.a
else
LIBC=$(TOPDIR)/libc/libc.a
endif
LIB_CPU=i86
LIB_OS=ELKS

.S.o:
	gcc -E -traditional $(INCS) $(SDEFS) -o $*.tmp $<
	$(AS) $(ASFLAGS) -o $*.o $*.tmp
	rm -f $*.tmp

ifdef MULTISUBDIR
build-ml/$(MULTISUBDIR)/%.o: %.S
	gcc -E -traditional $(INCS) $(SDEFS) -o $@.tmp $<
	$(AS) $(ASFLAGS) -o $@ $@.tmp
	rm -f $@.tmp
endif

.s.o:
	$(AS) $(ASFLAGS) -o $*.o $<

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<