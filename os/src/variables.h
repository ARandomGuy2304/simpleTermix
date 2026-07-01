#ifndef VARIABLES_H
#define VARIABLES_H

#define CURSOR_BLINK_INTERVAL 100000
#define NOTE_MAX 100000
#define CMD_BUFFER_MAX 100000

int cursor_x = 10;
int cursor_y = 10;
const int start_x = 10;
struct limine_framebuffer *fb;

int cursor_visible = 0;
uint32_t cursor_blink_counter = 0;

uint32_t current_text_color = 0xFFFFFF;
uint32_t current_bg_color = 0x000000;

char cmd_buffer[CMD_BUFFER_MAX];
int cmd_buffer_idx = 0;

int logged_in = 0;
char system_username[32] = {0};
char system_password[32] = {0};

int login_stage = 0;
char login_username[32] = {0};

char note[NOTE_MAX];

int shift_pressed = 0;
int caps_lock = 0;

#define FS_MAX_FILES 64
#define FS_NAME_MAX 32
#define FS_CONTENT_MAX 4096

typedef struct {
    char name[FS_NAME_MAX];
    char content[FS_CONTENT_MAX];
    int used;
} file_t;

file_t filesystem[FS_MAX_FILES];
int fs_file_count = 0;

#endif
