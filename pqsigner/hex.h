// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#ifndef HEX
#define HEX
void puthex(const uint8_t ch);
void putinthex(const uint32_t n);
void puthexn(uint8_t *p, int n);
void hexdump(void *buf, int len);
#endif
