#ifndef MAIN_H
#define MAIN_H
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "font.h"
#include "limine.h"
#include "print.h"

volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

volatile struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST_ID,
    .revision = 0
};

volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
volatile void *limine_requests[] = {
    (void *)&framebuffer_request,
    (void *)&module_request,
    (void *)&memmap_request,
    NULL
};

inline uint64_t get_usable_ram(void) {
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

inline uint64_t get_total_ram(void) {
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

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

const char scancode_table[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, '*', 0, ' '
};

const char scancode_shift_table[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0,  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    0, '*', 0, ' '
};

char keyboard_get_key(void) {
    if ((inb(0x64) & 1) == 0)
        return 0;

    uint8_t scancode = inb(0x60);

    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return 0;
    }

    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
        return 0;
    }

    if (scancode == 0x3A) {
        caps_lock = !caps_lock;
        return 0;
    }

    if (scancode & 0x80)
        return 0;

    char c;

    if (shift_pressed)
        c = scancode_shift_table[scancode];
    else
        c = scancode_table[scancode];

    if (caps_lock && c >= 'a' && c <= 'z') {
        c -= 32;
    }
    else if (caps_lock && shift_pressed &&
             c >= 'A' && c <= 'Z') {
        c += 32;
    }

    return c;
}

void cpu_brand(char brand[49]) {
    uint32_t *p = (uint32_t *)brand;

    for (uint32_t leaf = 0x80000002; leaf <= 0x80000004; leaf++) {
        uint32_t eax, ebx, ecx, edx;

        __asm__ volatile (
            "cpuid"
            : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
            : "a"(leaf)
        );

        *p++ = eax;
        *p++ = ebx;
        *p++ = ecx;
        *p++ = edx;
    }

    brand[48] = '\0';
}

void init_storage(void) {
    if (module_request.response == NULL || module_request.response->module_count < 1) {
        const char *default_user = "admin";
        const char *default_pass = "password123";
        int i = 0;
        while (default_user[i] != '\0' && i < 31) {
            system_username[i] = default_user[i];
            i++;
        }
        system_username[i] = '\0';
        
        i = 0;
        while (default_pass[i] != '\0' && i < 31) {
            system_password[i] = default_pass[i];
            i++;
        }
        system_password[i] = '\0';
        return;
    }

    struct limine_file *file = module_request.response->modules[0];
    char *data = (char *)file->address;
    size_t size = file->size;
    data[size - 1] = '\0';

    int idx = 0;
    while (*data != ' ' && *data != '\0' && idx < 31) {
        system_username[idx++] = *data++;
    }
    system_username[idx] = '\0';
    if (*data == ' ') data++;

    idx = 0;
    while (*data != ' ' && *data != '\0' && *data != '\n' && *data != '\r' && idx < 31) {
        system_password[idx++] = *data++;
    }
    system_password[idx] = '\0';
}

int hex_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

int parse_hex_color(const char *str, uint32_t *color) {
    uint32_t value = 0;

    for (int i = 0; i < 6; i++) {
        int digit = hex_digit(str[i]);
        if (digit < 0) return 0;
        value = (value << 4) | digit;
    }

    if (str[6] != '\0')
        return 0;

    *color = value;
    return 1;
}

inline uint64_t bytes_to_mb(uint64_t bytes) {
    return bytes / 1000000;
}

void execute_command(char *cmd) {
    char *args = "";
    for (int i = 0; cmd[i] != '\0'; i++) {
        if (cmd[i] == ' ') {
            cmd[i] = '\0';
            args = &cmd[i + 1];
            break;
        }
    }

    if (!logged_in) {
        if (login_stage == 0) {
            int i = 0;

            while (cmd[i] && i < 31) {
                login_username[i] = cmd[i];
                i++;
            }

            login_username[i] = '\0';

            login_stage = 1;
            terminal_print("\nPassword: ");
            return;
        }

        if (login_stage == 1) {
            if (strcmp(login_username, system_username) == 0 && strcmp(cmd, system_password) == 0) {
                logged_in = 1;
                login_stage = 0;

                terminal_print("\n\n> ");
            } else {
                login_stage = 0;

                terminal_print("\nWrong password, try again.\n");
                terminal_print("Username: ");
            }
            return;
        }
    }

    if (strcmp(cmd, "help") == 0) {
        terminal_print("Available commands:\n");
        terminal_print("  help                - Show this application menu\n");
        terminal_print("  clear               - Clear the terminal\n");
        terminal_print("  sysinfo             - Display basic information\n");
        terminal_print("  sleep               - Freeze the OS\n");
        terminal_print("  echo <text>         - Print arguments to screen\n");
        terminal_print("  logout              - Log out\n");
        terminal_print("  blue                - Switch to blue display color\n");
        terminal_print("  green               - Switch to retro green display color\n");
        terminal_print("  red                 - Switch to dark red text mode\n");
        terminal_print("  white               - Reset interface text to white\n");
        terminal_print("  hex <RRGGBB>        - Set text color using hexadecimal RGB\n");
        terminal_print("  background <RRGGBB> - Set screen background color using hexadecimal RGB\n");
        terminal_print("  write_note <text>   - Take a note and save it\n");
        terminal_print("  read_note           - Read your note\n");
    } 
    else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } 
    else if (strcmp(cmd, "sysinfo") == 0) {
        char width_buf[12];
        char height_buf[12];
        int_to_str(fb->width, width_buf);
        int_to_str(fb->height, height_buf);

        uint64_t total_mb = bytes_to_mb(get_total_ram());
        uint64_t usable_mb = bytes_to_mb(get_usable_ram());
        uint64_t used_mb = total_mb - usable_mb; 

        char brand[49];
        cpu_brand(brand);

        terminal_print("CPU: ");
        terminal_print(brand);
        terminal_print("\n");

        terminal_print("OS Kernel: simpleTermix-core-v1.4.1\n");
        terminal_print("Resolution: ");
        terminal_print(width_buf);
        terminal_print("x");
        terminal_print(height_buf);

        terminal_printf("\nRAM usage: %llu MB / %llu MB", used_mb, total_mb);    
    }
    else if (strcmp(cmd, "sleep") == 0) {
        __asm__ volatile("hlt");
    }
    else if (strcmp(cmd, "echo") == 0) {
        terminal_print(args);
    }
    else if (strcmp(cmd, "write_note") == 0) {
        int i = 0;

        while (args[i] && i < NOTE_MAX - 1) {
            note[i] = args[i];
            i++;
        }

        note[i] = '\0';

    }
    else if (strcmp(cmd, "read_note") == 0) {
        terminal_printf("%s", note);
    }
    else if (strcmp(cmd, "logout") == 0) {
        logged_in = 0;
        clear_screen();
    }
    else if (strcmp(cmd, "green") == 0) {
        current_text_color = 0x00FF00;
    }
    else if (strcmp(cmd, "red") == 0) {
        current_text_color = 0xFF0000;
    }
    else if (strcmp(cmd, "blue") == 0) {
        current_text_color = 0x0000FF;
    }
    else if (strcmp(cmd, "white") == 0) {
        current_text_color = 0xFFFFFF;
    }
    else if (strcmp(cmd, "hex") == 0) {
        uint32_t color;

        if (parse_hex_color(args, &color)) {
            current_text_color = color;
            terminal_print("Color updated.");
        } else {
            terminal_print("Usage: hex RRGGBB");
        }
    }
    else if (strcmp(cmd, "background") == 0) {
        uint32_t color;

        if (parse_hex_color(args, &color)) {
            current_bg_color = color;
            clear_screen();
            terminal_print("Background updated.");
        } else {
            terminal_print("Usage: background RRGGBB");
        }
    }
    else if (strcmp(cmd, "") == 0) {
    }
    else {
        terminal_print("Command not found: ");
        terminal_print(cmd);
    }

    terminal_print("\n> ");
}
