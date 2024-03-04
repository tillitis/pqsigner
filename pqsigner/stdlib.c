// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <tkey/assert.h>
#include <tkey/led.h>
#include <tkey/qemu_debug.h>

#include "io.h"
#include "stdlib.h"

void exit(int code)
{
	puts("exit code: ");
	putinthex(code);
	puts("\n");
	assert(1 == 2);
	__builtin_unreachable();
}
