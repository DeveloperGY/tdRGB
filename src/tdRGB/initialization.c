#include "td.h"

int TD_WIDTH = 0;
int TD_HEIGHT = 0;

_td_arena TD_ARENA;

char *TD_CHAR_BUFFER = NULL;
char *TD_PRINT_BUFFER = NULL;
td_color *TD_FG_COLOR_BUFFER = NULL;
td_color *TD_BG_COLOR_BUFFER = NULL;

int TD_CHAR_BUFFER_SIZE = 0;
int TD_PRINT_BUFFER_SIZE = 0;
int TD_FG_COLOR_BUFFER_SIZE = 0;
int TD_BG_COLOR_BUFFER_SIZE = 0;

struct termios old_settings;
struct termios new_settings;


void initialize_char_buffer();
void initialize_fg_color_buffer();
void initialize_bg_color_buffer();
void initialize_print_buffer();






int td_init(int width, int height)
{
    // " \x1b [ 4 8 ;  2 ; 0 0  0 ; 0 0  0 ; 0 0  0 m \x1b [ m"
    //   1    1 1 1 1  1 1 1 1  1 1 1 1  1 1 1 1  1 1 1    1 1
    //   1  + 19 + 2
    int fg_esc_code_size = 22;

    TD_CHAR_BUFFER_SIZE = width * height;
    TD_FG_COLOR_BUFFER_SIZE = width * height * sizeof(td_color);
    TD_BG_COLOR_BUFFER_SIZE = width * height * sizeof(td_color);
    TD_PRINT_BUFFER_SIZE = (width * height * 2 * (fg_esc_code_size + 1)) + height;
    // width * height * 2( fg_esc_code_size + 1) = each printed character (colors included))
    // + height = space for new lines and null terminator
    // characters are 1 byte so there is no need to multiply by sizeof(char)

    int total_buffer_size = TD_CHAR_BUFFER_SIZE + TD_FG_COLOR_BUFFER_SIZE + TD_BG_COLOR_BUFFER_SIZE + TD_PRINT_BUFFER_SIZE;



    TD_ARENA = _td_create_arena(total_buffer_size);

    if (!TD_ARENA.size)
    {
        TD_CHAR_BUFFER_SIZE = 0;
        TD_FG_COLOR_BUFFER_SIZE = 0;
        TD_FG_COLOR_BUFFER_SIZE = 0;
        TD_PRINT_BUFFER_SIZE = 0;
        return 0;
    }

    TD_WIDTH = width;
    TD_HEIGHT = height;



    initialize_char_buffer();
    initialize_fg_color_buffer();
    initialize_bg_color_buffer();
    initialize_print_buffer();

    tcgetattr(0, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new_settings);

    printf("\x1b[?25l\x1b[H\x1b[2J");

    return 1;
}


void td_terminate(int clear)
{
    TD_WIDTH = 0;
    TD_HEIGHT = 0;

    TD_CHAR_BUFFER = NULL;
    TD_FG_COLOR_BUFFER = NULL;
    TD_BG_COLOR_BUFFER = NULL;
    TD_PRINT_BUFFER = NULL;

    TD_CHAR_BUFFER_SIZE = 0;
    TD_FG_COLOR_BUFFER_SIZE = 0;
    TD_BG_COLOR_BUFFER_SIZE = 0;
    TD_PRINT_BUFFER_SIZE = 0;

    _td_free_arena(&TD_ARENA);


    if (clear)
    {
        printf("\x1b[H\x1b[2J");
    }

    printf("\n\x1b[?25h");

    tcsetattr(0, TCSANOW, &old_settings);

    return;
}




void initialize_char_buffer()
{
    TD_CHAR_BUFFER = (char *)_td_alloc_arena(&TD_ARENA, TD_CHAR_BUFFER_SIZE);

    for (int i=0; i<TD_CHAR_BUFFER_SIZE; i++)
    {
        TD_CHAR_BUFFER[i] = ' ';
    }

    return;
}

void initialize_fg_color_buffer()
{
    TD_FG_COLOR_BUFFER = (td_color *)_td_alloc_arena(&TD_ARENA, TD_FG_COLOR_BUFFER_SIZE);

    for (int i=0; i<(TD_FG_COLOR_BUFFER_SIZE / sizeof(td_color)); i++)
    {
        TD_FG_COLOR_BUFFER[i] = (td_color){0, 0, 0};
    }

    return;
}

void initialize_bg_color_buffer()
{
    TD_BG_COLOR_BUFFER = (td_color *)_td_alloc_arena(&TD_ARENA, TD_BG_COLOR_BUFFER_SIZE);

    for (int i=0; i<(TD_BG_COLOR_BUFFER_SIZE / sizeof(td_color)); i++)
    {
        TD_BG_COLOR_BUFFER[i] = (td_color){0, 0, 0};
    }

    return;
}

void initialize_print_buffer()
{
    TD_PRINT_BUFFER = (char *)_td_alloc_arena(&TD_ARENA, TD_PRINT_BUFFER_SIZE);

    return;
}