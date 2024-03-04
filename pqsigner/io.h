// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#ifndef IO
#define IO
#include <stdint.h>

char getchar(void);
void putchar(char c);
void puts(char *m);
void lf(void);
void puthex(uint8_t c);
void putinthex(const uint32_t n);
void puthexn(uint8_t *p, int n);
void hexdump(void *buf, int len);
#endif
