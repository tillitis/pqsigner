OBJCOPY ?= llvm-objcopy

LIBDIR ?= ../pqclean/dilithium3/clean/

P := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
TKEYLIBDIR ?= $(P)/../../tkey-libs

INCLUDE = -I $(LIBDIR) -I $(TKEYLIBDIR)/include -I .
LDFLAGS =-L $(LIBDIR) -ldilithium3_clean -T $(TKEYLIBDIR)/app.lds -L $(TKEYLIBDIR) -lcommon -lcrt0

CFLAGS = -target riscv32-unknown-none-elf -march=rv32iczmmul -mabi=ilp32 -mcmodel=medany \
    -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf \
    -fno-builtin-putchar -nostdlib -mno-relax -flto -g \
    -Wall -Werror=implicit-function-declaration \
    $(INCLUDE) -DTKEY # -DQEMU_DEBUG # -DSTATICKEYS

CC=clang

all: pqsigner.bin

# Turn elf into bin for device
%.bin: %.elf
	$(OBJCOPY) --input-target=elf32-littleriscv --output-target=binary $^ $@
	chmod a-x $@

OBJS=main.o stdlib.o malloc.o ../pqclean/fips202.o io.o hex.o static-keys.o
pqsigner.elf: ../pqclean/dilithium3/clean/libdilithium3_clean.a $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): $(TKEYLIBDIR)/include/tkey/tk1_mem.h *.h

../pqclean/dilithium3/clean/libdilithium3_clean.a:
	make -C ../pqclean/dilithium3/clean clean
	make -C ../pqclean/dilithium3/clean

.PHONY: clean
clean:
	$(RM) pqsigner.bin pqsigner.elf *.o
	$(RM) ../pqclean/*.o
	make -C ../pqclean/dilithium3 clean

# Uses ../.clang-format
FMTFILES=*.[ch]

.PHONY: fmt
fmt:
	clang-format --dry-run --ferror-limit=0 $(FMTFILES)
	clang-format --verbose -i $(FMTFILES)
.PHONY: checkfmt
checkfmt:
	clang-format --dry-run --ferror-limit=0 --Werror $(FMTFILES)
