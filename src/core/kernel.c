#include "bios_colour_attributes.h"

// No stadnardised way to detect 64-bit vs 32-bit architectures. So this will have to do
#if defined (__alpha__) || defined (__ia64__) || defined (__x86_64__) || defined (_WIN64) || defined (__LP64__) || defined (__LLP64__)
    typedef unsigned __int64  __kernel_uintptr_t;
#else
    typedef unsigned int __kernel_uintptr_t;
#endif

// ==== KERNEL CONSTANTS ====

static const __kernel_uintptr_t VIDEO_MEMORY_ADDRESS = 0xb8000;
static const unsigned char VIDEO_MAX_LINES = 25;
static const unsigned char VIDEO_MAX_CHAR_PER_LINE = 80;
static const unsigned char BYTES_PER_CHAR = 2;
static const char CLEAR_CHARS[2] = { ' ', BIOS_COLOUR_ATTR_GREEN };

// ==== MAIN ====

void kernelMain(void) {
    const char* string = "C x86 Kernel";
    char* videoMemPtr = (char*) VIDEO_MEMORY_ADDRESS;

    for (int i = 0; i < VIDEO_MAX_LINES * VIDEO_MAX_CHAR_PER_LINE * BYTES_PER_CHAR; i += 2) {
        videoMemPtr[i] = CLEAR_CHARS[0];
        videoMemPtr[i + 1] = CLEAR_CHARS[1];
    }

    unsigned int i = 0;
    unsigned int j = 0;
    while (string[j] != '\0') {
        videoMemPtr[i] = string[j];
        videoMemPtr[i+1] = CLEAR_CHARS[1];
        j++;
        i += 2;
    }
}