// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <stdint.h>
#ifdef HOST
#include <stdio.h>
#include <string.h>
#endif

#ifdef TKEY
#include "io.h"
#include <tkey/lib.h>
#endif

#include "hex.h"

static char hexnibble(const uint8_t ch)
{
	switch (ch) {
	case 0x0:
		return '0';
	case 0x1:
		return '1';
	case 0x2:
		return '2';
	case 0x3:
		return '3';
	case 0x4:
		return '4';
	case 0x5:
		return '5';
	case 0x6:
		return '6';
	case 0x7:
		return '7';
	case 0x8:
		return '8';
	case 0x9:
		return '9';
	case 0xa:
		return 'a';
	case 0xb:
		return 'b';
	case 0xc:
		return 'c';
	case 0xd:
		return 'd';
	case 0xe:
		return 'e';
	case 0xf:
		return 'f';
	}

	return '0';
}

void puthex(const uint8_t ch)
{
	putchar(hexnibble(ch >> 4 & 0x0f));
	putchar(hexnibble(ch & 0x0f));
}

void putinthex(const uint32_t n)
{
	uint8_t buf[4];

	memcpy(buf, &n, 4);
	puts("0x");
	for (int i = 3; i > -1; i--) {
		puthex(buf[i]);
	}
}

void puthexn(uint8_t *p, int n)
{
	for (int i = 0; i < n; i++) {
		puthex(p[i]);
	}
}

void hexdump(void *buf, int len)
{
	uint8_t *byte_buf = (uint8_t *)buf;

	for (int i = 0; i < len; i++) {
		puthex(byte_buf[i]);
		if (i % 2 == 1) {
			putchar(' ');
		}

		if (i != 1 && i % 16 == 1) {
			puts("\n");
		}
	}

	puts("\n");
}
