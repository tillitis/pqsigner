// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <stddef.h>
#include <stdint.h>

#ifdef TKEY
#include <tkey/qemu_debug.h>
#endif

#include "malloc.h"

struct malloc_buf malloc_buf = {0};

// WARNING! Incredibly stupid malloc() replacement. It just returns
// the same buffer over and over. The only protection is that it
// returns NULL if the buffer is already allocated.
//
// You will have to sett malloc_buf.buf to something big enough
// yourself for all your use cases before using it.
void *mymalloc(size_t n)
{
	if (malloc_buf.buf == NULL || malloc_buf.count > 0 ||
	    n > malloc_buf.size) {
		return NULL;
	}

	malloc_buf.count++;
	return malloc_buf.buf;
}

// Not implemented since we return the same buffer over and over in
// mymalloc()
void myfree(void *p)
{
	malloc_buf.count--;
}
