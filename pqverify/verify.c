// Copyright (C) Tillitis AB
// SPDX-License-Identifier: GPL-2.0-only

#include <api.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hex.h"

int decodehexsig(uint8_t hexsig[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES * 2],
		 uint8_t sig[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES])
{
	return parsehex(hexsig, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES * 2, sig,
			PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES);
}

int main(int argc, char **argv)
{
	uint8_t pubkey[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES];
	uint8_t hexpk[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES * 2];
	uint8_t sig[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES];
	uint8_t hexsig[PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES * 2];
	uint8_t msg[22] = "Håll den som en gyro!";
	size_t msglen = 22;
	int fd;

	if (argc != 3) {
		printf("Usage: pqverify <sig file> <public key files>\n");
		exit(1);
	}

	// Open file for sig and pubkey
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		printf("Couldn't open %s\n", argv[1]);
		exit(1);
	}

	printf("Reading signature file %s with %d bytes\n", argv[1],
	       PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES * 2);
	if (read(fd, hexsig, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES * 2) < 0) {
		printf("Couldn't read\n");
		exit(1);
	}

	close(fd);

	fd = open(argv[2], O_RDONLY);
	if (fd < 0) {
		printf("Couldn't open %s\n", argv[2]);
		exit(1);
	}

	printf("Reading public key file %s with %d bytes\n", argv[2],
	       PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES * 2);

	if (read(fd, hexpk,
		 PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_PUBLICKEYBYTES * 2) < 0) {
		printf("Couldn't read\n");
		exit(1);
	}

	close(fd);

	// Decode hex
	if (decodehexsig(hexsig, sig) < 0) {
		printf("Couldn't decode hex signature\n");
		exit(1);
	}

	// hexdump(sig, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES);

	if (decodehexsig(hexpk, pubkey) < 0) {
		printf("Couldn't decode hex public key\n");
		exit(1);
	}

	// hexdump(sig, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES)

	if (PQCLEAN_DILITHIUM3_CLEAN_crypto_sign_verify(
		sig, PQCLEAN_DILITHIUM3_CLEAN_CRYPTO_BYTES, msg, msglen,
		pubkey) != 0) {
		puts("Failed to verify signature\n");
		exit(1);
	}

	puts("Verified!\r\n");

	exit(0);
}
