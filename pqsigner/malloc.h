// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#ifndef MALLOC
#define MALLOC

struct malloc_buf {
	void *buf;
	size_t size;
	int count;
};

// Always set this malloc.buf and .size to a locally allocated buffer,
// typically on the stack, before calling mymalloc().
extern struct malloc_buf malloc_buf;

#define malloc mymalloc
#define free myfree

void *mymalloc(size_t n);
void myfree(void *p);
#endif
