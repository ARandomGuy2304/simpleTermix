#include "main.h"

void kernel_main(void) {
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        for (;;) { __asm__("hlt"); }
    }

    fb = framebuffer_request.response->framebuffers[0];
    clear_screen();
    
    init_storage();
    
    terminal_print("              @@                                                                                        @@\n");
    terminal_print("              @@                         @@@@                @@@@@@@@                                   @@\n");
    terminal_print("              @@                         @@@@                @@@@@@@@                                   @@\n");
    terminal_print("                                           @@                   @@\n");
    terminal_print("   @@@@@    @@@@     @@ @ @@   @@ @@@      @@        @@@@       @@       @@@@     @@ @@@@  @@ @ @@    @@@@     @@@  @@@\n");
    terminal_print(" @@@@@@@@   @@@@     @@@@@@@@  @@@@@@@     @@       @@@@@@      @@      @@@@@@    @@@@@@@  @@@@@@@@   @@@@      @@  @@\n");
    terminal_print(" @@     @     @@     @@ @@ @@  @@@  @@@    @@      @@    @@     @@     @@    @@   @@@      @@ @@ @@     @@       @@@@\n");
    terminal_print(" @@@@@        @@     @@ @@ @@  @@    @@    @@      @@@@@@@@     @@     @@@@@@@@   @@       @@ @@ @@     @@       @@@@\n");
    terminal_print("  @@@@@@      @@     @@ @@ @@  @@    @@    @@      @@@@@@@@     @@     @@@@@@@@   @@       @@ @@ @@     @@        @@\n");
    terminal_print("       @@     @@     @@ @@ @@  @@    @@    @@      @@           @@     @@         @@       @@ @@ @@     @@       @@@@\n");
    terminal_print(" @@    @@     @@     @@ @@ @@  @@@  @@@    @@      @@@    @     @@     @@@    @   @@       @@ @@ @@     @@       @@@@\n");
    terminal_print(" @@@@@@@@  @@@@@@@@  @@ @@ @@  @@@@@@@     @@@@@    @@@@@@@     @@      @@@@@@@   @@       @@ @@ @@  @@@@@@@@   @@  @@\n");
    terminal_print("  @@@@@    @@@@@@@@  @@ @@ @@  @@ @@@       @@@@     @@@@@      @@       @@@@@    @@       @@ @@ @@  @@@@@@@@  @@@  @@@\n");
    terminal_print("                               @@\n");
    terminal_print("                               @@\n");
    terminal_print("                               @@\n\n");
    terminal_print("simpleTermix-v1.4.0\n");
    terminal_print("Username: ");

    for (;;) {
        char key = keyboard_get_key();

        if (key != 0) {
            if (key == '\n') {
                cmd_buffer[cmd_buffer_idx] = '\0';
                terminal_print("\n");

                execute_command(cmd_buffer);
                cmd_buffer_idx = 0;
            }
            else if (key == '\b') {
                if (cmd_buffer_idx > 0) {
                    cmd_buffer_idx--;
                    terminal_write_char(key);
                }
            }
            else {
                if (cmd_buffer_idx < CMD_BUFFER_MAX - 1) {
                    cmd_buffer[cmd_buffer_idx++] = key;
                    terminal_write_char(key);
                }
            }
            
            cursor_visible = 1;
            cursor_blink_counter = 0;
            update_cursor_render(1);
        } else {
            cursor_blink_counter++;
            if (cursor_blink_counter >= CURSOR_BLINK_INTERVAL) {
                cursor_blink_counter = 0;
                cursor_visible = !cursor_visible;
                update_cursor_render(cursor_visible);
            }
        }

        __asm__ volatile("pause");
    }
}
