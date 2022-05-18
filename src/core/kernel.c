#include <inttypes.h>
#include <memory.h>

#include "bios_colour_attributes.h"

// ==== KERNEL CONSTANTS ====

static const uintptr_t VIDEO_MEMORY_ADDRESS = 0xb8000;
static const uint8_t VIDEO_MAX_LINES = 25;
static const uint8_t VIDEO_MAX_CHAR_PER_LINE = 80;
/* Not sure why, but if this is made a static const uint8_t then the refresh loop (first one)
 * doesn't clear the screen properly with memcpy, but if you have a preprocessor constant it
 * works perfectly. Probably some weird glibc 32-bit thing with manual linking.
 */
#define BYTES_PER_BIOS_CHAR 2
static const char CLEAR_CHARS[BYTES_PER_BIOS_CHAR] = { ' ', BIOS_COLOUR_ATTR_GREEN };

// ==== MAIN ====

void kernelMain(void) {
    const char* string = "C x86 Kernel";
    char* videoMemPtr = (char*) VIDEO_MEMORY_ADDRESS;
    for (int i = 0; i < VIDEO_MAX_LINES * VIDEO_MAX_CHAR_PER_LINE * BYTES_PER_BIOS_CHAR; i += BYTES_PER_BIOS_CHAR) {
        memcpy(videoMemPtr + i, CLEAR_CHARS, BYTES_PER_BIOS_CHAR * sizeof(char));
    }
    for (int j = 0, i = 0; string[j] != '\0'; j++, i += BYTES_PER_BIOS_CHAR) {
        videoMemPtr[i] = string[j];
        videoMemPtr[i+1] = CLEAR_CHARS[1];
    }
}