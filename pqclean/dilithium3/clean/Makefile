# This Makefile can be used with GNU Make or BSD Make

LIBDIR ?= ../../tkey-libs
LIB=libdilithium3_clean.a
HEADERS=api.h ntt.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h 
OBJECTS=ntt.o packing.o poly.o polyvec.o reduce.o rounding.o sign.o symmetric-shake.o 

CC = clang

CFLAGS = -target riscv32-unknown-none-elf -march=rv32iczmmul -mabi=ilp32 -mcmodel=medany \
   -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf \
   -fno-builtin-putchar -nostdlib -mno-relax -flto -g \
   -Wall -Werror=implicit-function-declaration -Wextra -Wpedantic -Werror -Wmissing-prototypes -Wredundant-decls -std=c99 \
   -I $(LIBDIR)/include  \
   -std=c99 -I../.. $(EXTRAFLAGS) -DTKEY

all: $(LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(AR) -r $@ $(OBJECTS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
