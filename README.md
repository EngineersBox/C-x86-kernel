# C-x86-kernel

A Kernel in x86 and C

## Dependencies

In order to build and run the kernel, there are a few tools you will need to have installed:

* NASM
* GCC
* QEMU

## Usage

This can be compiled for both UNIX and WSl2 systems, provided by the
Makefile targets `unix` and `windows` respectively.

By default, the linker assumes that the 32-bit libc libraries for linking are in `/usr/lib32`.
If this is not the case, you can alter this by providing an override to `LIB32_PATH` with the make targets, for example:

```shell
make LIB32_PATH=/usr/lib32 unix
```
