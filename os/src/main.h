#ifndef MAIN_H
#define MAIN_H
#endif

#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "limine.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

static volatile struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile void *limine_requests[] = {
    (void *)&framebuffer_request,
    (void *)&module_request,
    NULL
};

static const uint8_t font[128][8] = {
    [' '] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    ['!'] = {0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00},
    ['"'] = {0x24, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00},
    ['#'] = {0x24, 0x24, 0x7E, 0x24, 0x7E, 0x24, 0x24, 0x00},
    ['$'] = {0x10, 0x3C, 0x50, 0x38, 0x14, 0x3C, 0x10, 0x00},
    ['%'] = {0x62, 0x64, 0x08, 0x10, 0x20, 0x26, 0x46, 0x00},
    ['&'] = {0x1C, 0x22, 0x14, 0x28, 0x54, 0x22, 0x5D, 0x00},
    ['\'']= {0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00},
    ['('] = {0x0C, 0x10, 0x20, 0x20, 0x20, 0x10, 0x0C, 0x00},
    [')'] = {0x30, 0x08, 0x04, 0x04, 0x04, 0x08, 0x30, 0x00},
    ['*'] = {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, 0x00, 0x00},
    ['+'] = {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00},
    [','] = {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x08, 0x10},
    ['-'] = {0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00},
    ['.'] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00},
    ['/'] = {0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00},
    
    ['0'] = {0x3C, 0x46, 0x4A, 0x52, 0x62, 0x62, 0x3C, 0x00},
    ['1'] = {0x18, 0x28, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00},
    ['2'] = {0x3C, 0x42, 0x02, 0x0C, 0x30, 0x40, 0x7E, 0x00},
    ['3'] = {0x3C, 0x42, 0x02, 0x1C, 0x02, 0x42, 0x3C, 0x00},
    ['4'] = {0x04, 0x0C, 0x14, 0x24, 0x7E, 0x04, 0x04, 0x00},
    ['5'] = {0x7E, 0x40, 0x7C, 0x02, 0x02, 0x42, 0x3C, 0x00},
    ['6'] = {0x3C, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x3C, 0x00},
    ['7'] = {0x7E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10, 0x00},
    ['8'] = {0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x3C, 0x00},
    ['9'] = {0x3C, 0x42, 0x42, 0x3E, 0x02, 0x02, 0x3C, 0x00},
    
    [':'] = {0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00},
    [';'] = {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x08, 0x10},
    ['<'] = {0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00},
    ['='] = {0x00, 0x00, 0x3E, 0x00, 0x3E, 0x00, 0x00, 0x00},
    ['>'] = {0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x00},
    ['?'] = {0x3C, 0x42, 0x02, 0x0C, 0x18, 0x00, 0x18, 0x00},
    ['@'] = {0x3C, 0x42, 0x5A, 0x6A, 0x6A, 0x4E, 0x40, 0x3C},
    
    ['A'] = {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00},
    ['B'] = {0x7C, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00},
    ['C'] = {0x3C, 0x42, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00},
    ['D'] = {0x78, 0x44, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00},
    ['E'] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x7E, 0x00},
    ['F'] = {0x7E, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x00},
    ['G'] = {0x3C, 0x42, 0x40, 0x4E, 0x42, 0x42, 0x3C, 0x00},
    ['H'] = {0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00},
    ['I'] = {0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00},
    ['J'] = {0x1E, 0x02, 0x02, 0x02, 0x02, 0x42, 0x3C, 0x00},
    ['K'] = {0x42, 0x44, 0x48, 0x70, 0x48, 0x44, 0x42, 0x00},
    ['L'] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00},
    ['M'] = {0x42, 0x66, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x00},
    ['N'] = {0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x42, 0x00},
    ['O'] = {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00},
    ['P'] = {0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40, 0x00},
    ['Q'] = {0x3C, 0x42, 0x42, 0x42, 0x42, 0x4A, 0x3C, 0x02},
    ['R'] = {0x7C, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42, 0x00},
    ['S'] = {0x3C, 0x42, 0x40, 0x3C, 0x02, 0x42, 0x3C, 0x00},
    ['T'] = {0x7E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00},
    ['U'] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00},
    ['V'] = {0x42, 0x42, 0x42, 0x42, 0x24, 0x24, 0x18, 0x00},
    ['W'] = {0x42, 0x42, 0x42, 0x42, 0x5A, 0x66, 0x42, 0x00},
    ['X'] = {0x42, 0x24, 0x18, 0x18, 0x18, 0x24, 0x42, 0x00},
    ['Y'] = {0x42, 0x42, 0x24, 0x18, 0x18, 0x18, 0x18, 0x00},
    ['Z'] = {0x7E, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00},
    
    ['['] = {0x3E, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E, 0x00},
    ['\\']= {0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00},
    [']'] = {0x3E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x3E, 0x00},
    ['^'] = {0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00},
    ['_'] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E},
    ['`'] = {0x30, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00},
    
    ['a'] = {0x00, 0x00, 0x3C, 0x02, 0x3E, 0x42, 0x3E, 0x00},
    ['b'] = {0x40, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x7C, 0x00},
    ['c'] = {0x00, 0x00, 0x3C, 0x42, 0x40, 0x42, 0x3C, 0x00},
    ['d'] = {0x02, 0x02, 0x3E, 0x42, 0x42, 0x42, 0x3E, 0x00},
    ['e'] = {0x00, 0x00, 0x3C, 0x42, 0x7E, 0x40, 0x3C, 0x00},
    ['f'] = {0x1C, 0x22, 0x20, 0x7C, 0x20, 0x20, 0x20, 0x00},
    ['g'] = {0x00, 0x00, 0x3E, 0x42, 0x42, 0x3E, 0x02, 0x3C},
    ['h'] = {0x40, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x00},
    ['i'] = {0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x1C, 0x00},
    ['j'] = {0x04, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x44, 0x38},
    ['k'] = {0x40, 0x40, 0x44, 0x48, 0x70, 0x48, 0x44, 0x00},
    ['l'] = {0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00},
    ['m'] = {0x00, 0x00, 0x6C, 0x92, 0x92, 0x92, 0x92, 0x00},
    ['n'] = {0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x00}, 
    ['o'] = {0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x3C, 0x00},
    ['p'] = {0x00, 0x00, 0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40},
    ['q'] = {0x00, 0x00, 0x3E, 0x42, 0x42, 0x3E, 0x02, 0x02},
    ['r'] = {0x00, 0x00, 0x5C, 0x62, 0x40, 0x40, 0x40, 0x00},
    ['s'] = {0x00, 0x00, 0x3E, 0x40, 0x3C, 0x02, 0x7C, 0x00},
    ['t'] = {0x08, 0x08, 0x3E, 0x08, 0x08, 0x08, 0x06, 0x00},
    ['u'] = {0x00, 0x00, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00},
    ['v'] = {0x00, 0x00, 0x42, 0x42, 0x24, 0x24, 0x18, 0x00},
    ['w'] = {0x00, 0x00, 0x42, 0x42, 0x5A, 0x66, 0x42, 0x00},
    ['x'] = {0x00, 0x00, 0x42, 0x24, 0x18, 0x24, 0x42, 0x00},
    ['y'] = {0x00, 0x00, 0x42, 0x42, 0x24, 0x18, 0x10, 0x60},
    ['z'] = {0x00, 0x00, 0x7E, 0x04, 0x08, 0x10, 0x7E, 0x00},
    
    ['{'] = {0x0C, 0x10, 0x10, 0x20, 0x10, 0x10, 0x0C, 0x00},
    ['|'] = {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00},
    ['}'] = {0x30, 0x08, 0x08, 0x04, 0x08, 0x08, 0x30, 0x00},
    ['~'] = {0x00, 0x00, 0x32, 0x4D, 0x00, 0x00, 0x00, 0x00}
};

static int cursor_x = 10;
static int cursor_y = 10;
static const int start_x = 10;
static struct limine_framebuffer *fb;

static int cursor_visible = 0;
static uint32_t cursor_blink_counter = 0;
#define CURSOR_BLINK_INTERVAL 100000

static uint32_t current_text_color = 0xFFFFFF;
static uint32_t current_bg_color = 0x000000;

#define CMD_BUFFER_MAX 256
static char cmd_buffer[CMD_BUFFER_MAX];
static int cmd_buffer_idx = 0;

static int logged_in = 0;
static char system_username[32] = {0};
static char system_password[32] = {0};

static int login_stage = 0;
static char login_username[32] = {0};

static int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

static void int_to_str(uint32_t num, char *str) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

static void str_to_int(const char *str, uint64_t *out) {
    uint64_t result = 0;

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    *out = result;
}

void ull_to_str(unsigned long long value, char *buf) {
    char temp[21];
    int i = 0;

    if (value == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }

    int j = 0;
    while (i > 0) {
        buf[j++] = temp[--i];
    }
    buf[j] = '\0';
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static int shift_pressed = 0;
static int caps_lock = 0;

static const char scancode_table[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, '*', 0, ' '
};

static const char scancode_shift_table[128] = {
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

void terminal_print(const char *str);

void draw_char(char c, int x, int y, uint32_t color) {
    if (!fb) return;
    uint32_t *fb_ptr = (uint32_t *)fb->address;
    size_t stride = fb->pitch / 4; 

    for (int row = 0; row < 8; row++) {
        uint8_t font_row = font[(uint8_t)c][row];
        for (int col = 0; col < 8; col++) {
            size_t pixel_index = (y + row) * stride + (x + col);
            if (font_row & (0x80 >> col)) {
                fb_ptr[pixel_index] = color;
            } else {
                fb_ptr[pixel_index] = current_bg_color;
            }
        }
    }
}

void clear_screen(void) {
    if (!fb) return;
    uint32_t *fb_ptr = (uint32_t *)fb->address;
    size_t total_pixels = (fb->pitch / 4) * fb->height;
    for (size_t i = 0; i < total_pixels; i++) {
        fb_ptr[i] = current_bg_color;
    }
    cursor_x = start_x;
    cursor_y = 10;
}

void clear_char_at(int x, int y) {
    if (!fb) return;
    uint32_t *fb_ptr = (uint32_t *)fb->address;
    size_t stride = fb->pitch / 4;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            fb_ptr[(y + row) * stride + (x + col)] = current_bg_color;
        }
    }
}

void update_cursor_render(int show) {
    if (show) {
        draw_char('_', cursor_x, cursor_y, current_text_color);
    } else {
        clear_char_at(cursor_x, cursor_y);
    }
}

void terminal_write_char(char c) {
    if (!fb) return;

    update_cursor_render(0);

    if (c == '\n') {
        cursor_x = start_x;
        cursor_y += 12;
    } 
    else if (c == '\b') {
        if (cursor_x > start_x + 16) { 
            cursor_x -= 8;
            clear_char_at(cursor_x, cursor_y);
        }
    } 
    else {
        draw_char(c, cursor_x, cursor_y, current_text_color);
        cursor_x += 8;

        if (cursor_x >= (int)fb->width - 10) {
            cursor_x = start_x;
            cursor_y += 12;
        }
    }

    if (cursor_y >= (int)fb->height - 20) {
        clear_screen();
        terminal_print("> ");
    }
}

void terminal_print(const char *str) {
    while (*str) {
        terminal_write_char(*str);
        str++;
    }
}

void terminal_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%' && *(format + 1) != '\0') {
            format++;

            if (*format == 'd') {
                int num = va_arg(args, int);
                char buf[12];
                int_to_str(num, buf);
                terminal_print(buf);

            } else if (*format == 's') {
                char *string = va_arg(args, char *);
                terminal_print(string);

            } else if (*format == 'l' &&
                       *(format + 1) == 'l' &&
                       *(format + 2) == 'u') {

                unsigned long long num =
                    va_arg(args, unsigned long long);

                char buf[21];
                ull_to_str(num, buf);
                terminal_print(buf);

                format += 2;

            } else if (*format == '%') {
                terminal_write_char('%');
            }

        } else {
            terminal_write_char(*format);
        }

        format++;
    }

    va_end(args);
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

static int hex_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int parse_hex_color(const char *str, uint32_t *color) {
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
        terminal_print("  mov_r15 <integer>   - Load the user input into the R15 register\n");
        terminal_print("  read_r15            - Read the value of the R15 register\n");
    } 
    else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } 
    else if (strcmp(cmd, "sysinfo") == 0) {
        char width_buf[12];
        char height_buf[12];
        int_to_str(fb->width, width_buf);
        int_to_str(fb->height, height_buf);

        char brand[49];
        cpu_brand(brand);

        terminal_print("CPU: ");
        terminal_print(brand);
        terminal_print("\n");

        terminal_print("OS Kernel: simpleTermix-core-v1.4.0\n");
        terminal_print("Target architecture: x86_64 (Long Mode)\n");
        terminal_print("Resolution: ");
        terminal_print(width_buf);
        terminal_print("x");
        terminal_print(height_buf);
    }
    else if (strcmp(cmd, "sleep") == 0) {
        __asm__ volatile("hlt");
    }
    else if (strcmp(cmd, "echo") == 0) {
        terminal_print(args);
    }
    else if (strcmp(cmd, "mov_r15") == 0) {
        uint64_t r15_input;
        str_to_int(args, &r15_input);
        
        __asm__ volatile(
            "mov %0, %%r15"
            :
            : "r"(r15_input)
            : "r15"
        );
    }
    else if (strcmp(cmd, "read_r15") == 0) {
        uint64_t r15_output;

        __asm__ volatile(
            "mov %%r15, %0"
            : "=r"(r15_output)
        );

        terminal_printf("%llu\n", r15_output);
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
