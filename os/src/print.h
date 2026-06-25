#ifndef PRINT_H
#define PRINT_H
#endif

#include "convert.h"
#include "variables.h"

void terminal_print(const char *str);

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
