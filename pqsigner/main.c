// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <api.h>
#include <stddef.h>
#include <stdint.h>

#include "malloc.h"
#include "static-keys.h"

#ifdef HOST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hex.h"
#endif

#ifdef TKEY
#include <tkey/led.h>
#include <tkey/lib.h>
#include <tkey/proto.h>
#include <tkey/qemu_debug.h>

#include "io.h"
#include "stdlib.h"
#endif

// clang-format off
#ifdef TKEY
static volatile uint32_t *cdi = (volatile uint32_t *) TK1_MMIO_TK1_CDI_FIRST;
#else
#ifndef STATICKEYS
static uint32_t cdi[32] = { 1 };
#endif
#endif
// clang-format on

#ifdef TKEY
void ledexit(uint32_t color)
{
	led_set(color);
	for (;;)
		;
	__builtin_unreachable();
}
#endif

#ifdef HOST
void ledexit(uint32_t color)
{
	exit(0);
}
#endif

void printkey(uint8_t *key, size_t keylen)
{
	for (int i = 0; i < keylen; i++) {
		puthex(key[i]);
	}
	puts("\n");
}

void printckey(uint8_t *key, size_t keylen)
{
	putchar('{');
	for (int i = 0; i < keylen; i++) {
		putchar('0');
		putchar('x');
		puthex(key[i]);
		putchar(',');
	}
	puts(" }");
}

int main(void)
{

	uint8_t secret[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_SECRETKEYBYTES] = {0};
	uint8_t pubkey[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES] = {0};
	uint8_t sig[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES];
	size_t siglen = 0;
	uint8_t msg[22] = "Håll den som en gyro!";
	size_t msglen = 22;
	uint8_t buf[8 * 1024]; // Our malloc memory

	malloc_buf.buf = &buf;
	malloc_buf.size = 8 * 1024;

	// Wait for terminal program to connect and a character to be
	// typed
	(void)getchar();

	puts("pqsigner\n");

#ifdef STATICKEYS
	memcpy(sk, static_sk, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_SECRETKEYBYTES);
	memcpy(pk, static_pk, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES);
#else
	if (PQCLEAN_DILITHIUM3_CLEAN_crypto_sign_keypair(pubkey, secret,
							 (uint8_t *)cdi) != 0) {
		puts("Failed to generate keypair\n");
		exit(1);
	}
#endif

#if 0
	puts("Private key: \n");
	printckey(secret, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_SECRETKEYBYTES);

	printckey(pubkey, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES);
#endif

	puts("Public key: \n");
	printkey(pubkey, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES);

	if (PQCLEAN_DILITHIUM3_CLEAN_crypto_sign_signature(
		sig, &siglen, msg, msglen, secret) != 0) {
		puts("Failed to sign message\n");
		exit(1);
	}

	puts("Signature: \n");
	puthexn(sig, siglen);
	puts("\n");

	if (PQCLEAN_DILITHIUM3_CLEAN_crypto_sign_verify(sig, siglen, msg,
							msglen, pubkey) != 0) {
		puts("Failed to verify signature\n");
		exit(1);
	}

	puts("Verified!\n");

	ledexit(2);
}
