// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <stddef.h>
#include <stdint.h>
#include <tkey/qemu_debug.h>

#include "malloc.h"

void *malloc_buf = NULL;

void *mymalloc(size_t n)
{
	qemu_puts("malloc returns: ");
	qemu_putinthex((uint32_t)malloc_buf);
	qemu_lf();

	return malloc_buf;
}

// Not implemented since we return the same buffer over and over in mymalloc()
void myfree(void *p)
{
}
