LIBDIR ?= ../pqclean/dilithium3/clean
INCLUDE = -I $(LIBDIR)

CC=clang
CFLAGS = $(INCLUDE) -Wall -g -DHOST
LDFLAGS =-L $(LIBDIR) -ldilithium3_clean_host

all: pqverify

OBJS=verify.o hex.o ../pqclean/fips202.o

pqverify: $(OBJS) ../pqclean/dilithium3/clean/libdilithium3_clean_host.a
	$(CC) $(CLIENTCFLAGS) -o $@ $(OBJS) $(LDFLAGS)

../pqclean/dilithium3/clean/libdilithium3_clean_host.a:
	make -C ../pqclean/dilithium3/clean clean
	rm -f ../pqclean/*.o
	make -C ../pqclean/dilithium3/clean -f Makefile.host

.PHONY: clean
clean:
	$(RM) pqverify *.o

# Uses ../.clang-format
FMTFILES=verify.c hex.[ch]

.PHONY: fmt
fmt:
	clang-format --dry-run --ferror-limit=0 $(FMTFILES)
	clang-format --verbose -i $(FMTFILES)
.PHONY: checkfmt
checkfmt:
	clang-format --dry-run --ferror-limit=0 --Werror $(FMTFILES)
