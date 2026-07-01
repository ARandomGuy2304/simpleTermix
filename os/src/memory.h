#ifndef MEMORY_H
#define MEMORY_H
#endif

#include <stdint.h>
#include "limine.h"

extern volatile struct limine_memmap_request memmap_request;

static inline uint64_t get_usable_ram(void) {
    if (!memmap_request.response)
        return 0;

    uint64_t total = 0;

    for (uint64_t i = 0; i < memmap_request.response->entry_count; i++) {
        struct limine_memmap_entry *entry =
            memmap_request.response->entries[i];

        if (entry->type == LIMINE_MEMMAP_USABLE)
            total += entry->length;
    }

    return total;
}

static inline uint64_t get_total_ram(void) {
    if (!memmap_request.response)
        return 0;

    uint64_t total = 0;

    for (uint64_t i = 0; i < memmap_request.response->entry_count; i++) {
        struct limine_memmap_entry *entry =
            memmap_request.response->entries[i];

        total += entry->length;
    }

    return total;
}

static inline uint64_t bytes_to_mb(uint64_t bytes) {
    return bytes / 1000000;
}
