#ifndef PANIC_H
#define PANIC_H

#include "memory.h"
#include "print.h"

void kernel_panic(void) {
        uint64_t usable_mb = bytes_to_mb(get_usable_ram());

	if (usable_mb <= 2000000) {
		clear_screen();
		terminal_print("KERNEL PANIC\n");
		terminal_print("============\n\n");
		terminal_print("Reason: Out of memory\n");
		terminal_printf("Memory left: %llu\n\n", usable_mb);

		terminal_print("CPU halted.");

		for(;;) __asm__ volatile("hlt");
	}
}

#endif
