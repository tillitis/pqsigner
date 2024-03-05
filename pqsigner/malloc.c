// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <stddef.h>
#include <stdint.h>

#ifdef TKEY
#include <tkey/qemu_debug.h>
#endif

#include "malloc.h"

void *malloc_buf = NULL;

void *mymalloc(size_t n)
{
	return malloc_buf;
}

// Not implemented since we return the same buffer over and over in
// mymalloc()
void myfree(void *p)
{
}
