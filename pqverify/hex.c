// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void hexdump(const void *buf, int len)
{
	uint8_t *byte_buf = (uint8_t *)buf;

	for (int i = 0; i < len; i++) {
		printf("%02x", byte_buf[i]);
		if (i % 2 == 1) {
			(void)putchar(' ');
		}

		if (i != 1 && i % 16 == 1) {
			putchar('\n');
		}
	}

	putchar('\n');
}

static int8_t hexnibble(char c)
{
	switch (c) {
	case '0':
		return 0x0;
	case '1':
		return 0x01;
	case '2':
		return 0x02;
	case '3':
		return 0x03;
	case '4':
		return 0x04;
	case '5':
		return 0x05;
	case '6':
		return 0x06;
	case '7':
		return 0x07;
	case '8':
		return 0x08;
	case '9':
		return 0x09;
	case 'a':
		return 0x0a;
	case 'b':
		return 0x0b;
	case 'c':
		return 0x0c;
	case 'd':
		return 0x0d;
	case 'e':
		return 0x0e;
	case 'f':
		return 0x0f;

	default:
		return -1;
	}
}

int8_t parsehexbyte(uint8_t *hex)
{
	int8_t val;

	val = hexnibble(hex[0]);

	if (val < 0) {
		return -1;
	}

	// Shift to make space for next value
	val = (val << 4);

	int8_t val2 = hexnibble(hex[1]);
	if (val2 < 0) {
		return -1;
	}

	// Add second value
	val = val | (val2 & 0x0f);

	return val;
}

int parsehex(uint8_t *hexbuf, size_t hexlen, uint8_t *buf, size_t buflen)
{
	if (hexlen != buflen * 2) {
		return -1;
	}

	for (int i = 0, j = 0; i < buflen; i++, j += 2) {
		buf[i] = parsehexbyte(&hexbuf[j]);
		if (buf[i] < 0) {
			return -1;
		}
	}

	return 0;
}

#if 0
// For testing
int main()
{
	uint8_t hex[6] = { 'f', 'f', '1', '1', 'c', '0'};
	uint8_t first;
	uint8_t second;
	uint8_t third;

	first = parsehexbyte(&hex[0]);
	if (first < 0) {
		exit(1);
	}

	if (first == 0xff) {
		printf("Win!\n");
	} else {
		printf("Lose! 0x%x\n", first);
	}

	second = parsehexbyte(&hex[2]);
	if (second < 0) {
		exit(1);
	}

	if (second == 0x11) {
		printf("Win!\n");
	} else {
		printf("Lose! 0x%x\n", second);
	}

	third = parsehexbyte(&hex[4]);
	if (third < 0) {
		exit(1);
	}

	if (third == 0xc0) {
		printf("Win!\n");
	} else {
		printf("Lose! 0x%x\n", third);
	}

	exit(0);
}
#endif
