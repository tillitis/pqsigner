# pqsigner

Simple PQ signer proof of concept for the Tillitis TKey and
accompanying verification program using [PQClean
library's](https://github.com/PQClean/PQClean) dilithium3.

`pqsigner` signs and verifies a hardcoded message and outputs the
public key and the signature over the message. It can be run both on
the Tillitis TKey and a host computer.

`pqverify` verifies the signature over the same message. It's meant to
run on the host.

If you want to build and use a static compiled-in key pair, compile
with `-DSTATICKEYS`.

## Building for TKey

```
cd pqsigner
./build.sh
```

## Building for host

```
cd pqsigner
make -f Makefile.host
```
## Running

### Host

```
$ ./pqsigner
```

Hit the return key.

### TKey

```
$ tkey-runapp pqsigner.bin 
Auto-detected serial port /dev/ttyACM0
Connecting to device on serial port /dev/ttyACM0 ...
Firmware name0:'tk1 ' name1:'mkdf' version:5
UDI: 01337:2:1:00000002
Loading app from pqsigner.bin onto device
```

Then attach a terminal program like picocom:

```
$ picocom -b 62500 /dev/ttyACM0
```

And press any key.

## Verifying independently

Build `pqverify` on the host:

```
cd pqverify
make
```

Copy the public key and the signature to their own files. On the host
machine client run:

`pqverify <signature-file> <public-key-file>`:

```
$ cd pqverify 
$ ./pqverify testdata/sig testdata/pk 
Reading signature file testdata/sig with 6586 bytes
Reading public key file testdata/pk with 3904 bytes
Verified!
```

## Other code

We copy the `PQClean/common/fips202.[ch]` files under `pqclean`
directory.

The entire `PQClean/crypto_sign/dilithium3/clean` is inlined under
`pqclean/dilithium3/clean`.

## Licenses and SPDX tags

Unless otherwise noted, the project sources are licensed under the
terms and conditions of the "GNU General Public License v2.0 only":

> Copyright Tillitis AB.
>
> These programs are free software: you can redistribute it and/or
> modify it under the terms of the GNU General Public License as
> published by the Free Software Foundation, version 2 only.
>
> These programs are distributed in the hope that they will be useful,
> but WITHOUT ANY WARRANTY; without even the implied warranty of
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
> General Public License for more details.

> You should have received a copy of the GNU General Public License
> along with this program. If not, see:
>
> https://www.gnu.org/licenses

See [LICENSE](LICENSE) for the full GPLv2-only license text.

External source code we have imported are isolated in their own
directories. They may be released under other licenses. This is noted
with a similar `LICENSE` file in every directory containing imported
sources.

The project uses single-line references to Unique License Identifiers
as defined by the Linux Foundation's [SPDX project](https://spdx.org/)
on its own source files, but not necessarily imported files. The line
in each individual source file identifies the license applicable to
that file.

The current set of valid, predefined SPDX identifiers can be found on
the SPDX License List at:

https://spdx.org/licenses/

All the files under `pqclean` are public domain as shown in the LICENSE
copied from the PQClean.
