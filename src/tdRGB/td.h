#ifndef TD_RGB_H
#define TD_RGB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termios.h>
#include <sys/select.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} td_color;

typedef struct
{
    void *block;
    unsigned int pointer;
    unsigned int size;
} _td_arena; 


extern int TD_WIDTH;
extern int TD_HEIGHT;

extern _td_arena TD_ARENA;

extern char *TD_CHAR_BUFFER;
extern char *TD_PRINT_BUFFER;
extern td_color *TD_FG_COLOR_BUFFER;
extern td_color *TD_BG_COLOR_BUFFER;

extern int TD_CHAR_BUFFER_SIZE;
extern int TD_PRINT_BUFFER_SIZE;
extern int TD_FG_COLOR_BUFFER_SIZE;
extern int TD_BG_COLOR_BUFFER_SIZE;

extern struct termios old_settings;
extern struct termios new_settings;


#ifdef __cplusplus // Initialization/Termination
extern "C" {
#endif

int td_init(int width, int height);
void td_terminate(int clear);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus // Drawing
extern "C" {
#endif

void td_display();

void td_drawPoint(int x, int y, char c, td_color fgColor, td_color bgColor);

void td_drawStrokeRect(int x, int y, unsigned int width, unsigned int height, char c, td_color fgColor, td_color bgColor);

void td_drawFillRect(int x, int y, unsigned int width, unsigned int height, char c, td_color fgColor, td_color bgColor);

void td_drawRect(int x, int y, unsigned int width, unsigned int height, char stroke, char fill, td_color strokeFGColor, td_color strokeBGColor, td_color fillFGColor, td_color fillBGColor);

void td_drawLine(int x1, int y1, int x2, int y2, char c, td_color fgColor, td_color bgColor);

void td_drawTextHorizontal(int x, int y, const char *str, td_color fgColor, td_color bgColor);

void td_drawTextVertical(int x, int y, const char *str, td_color fgColor, td_color bgColor);

#ifdef __cplusplus
}
#endif






#ifdef __cplusplus // Helpers
extern "C" {
#endif

char getch(unsigned int max_wait_time);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus // Arena
extern "C" {
#endif

_td_arena _td_create_arena(unsigned int block_size);
void _td_free_arena(_td_arena *arena);
void *_td_alloc_arena(_td_arena *arena, unsigned int size);

#ifdef __cplusplus // End Arena
}
#endif

#endif