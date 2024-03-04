// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <stddef.h>
#include <stdint.h>
#include <tkey/lib.h>
#include <tkey/proto.h>

#include "io.h"

char getchar(void)
{
	return readbyte();
}

void putchar(char c)
{
	writebyte(c);
}

void puts(char *m)
{
	for (char *c = m; *c != '\0'; c++) {
		if (*c == '\n') {
			writebyte('\r');
		}

		writebyte(*c);
	}
}
