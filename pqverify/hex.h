// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#ifndef HEX
#define HEX
#include <stddef.h>
#include <stdint.h>

void hexdump(const void *buf, int len);
int8_t parsehexbyte(uint8_t *hex);
int parsehex(uint8_t *hexbuf, size_t hexlen, uint8_t *buf, size_t buflen);
#endif
