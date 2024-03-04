// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#ifndef MALLOC
#define MALLOC

// Always set this to a locally allocated buffer, typically on the
// stack, before calling mymalloc().
extern void *malloc_buf;

#define malloc mymalloc
#define free myfree

void *mymalloc(size_t n);
void myfree(void *p);
#endif
