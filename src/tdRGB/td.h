#ifndef TD_RGB_H
#define TD_RGB_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Struct Definitions
 */

/**
 * @brief An arena type used internally by td rgb
 */
typedef struct
{
    void *block;
    unsigned int pointer;
    unsigned int size;
} _td_arena;


typedef struct
{
    int red;
    int green;
    int blue;
} Color;

/**
 * End Struct Definitions
 */


/**
 * Globals
 */

extern int _TD_WIDTH;
extern int _TD_HEIGHT;
extern _td_arena _TD_ARENA;
extern char **_TD_CHAR_BUFFER;
extern char *_TD_PRINT_BUFFER;
extern Color **_TD_FG_COLOR_BUFFER;
extern Color **_TD_BG_COLOR_BUFFER;

/**
 * End Globals
 */




/**
 * Internal Arena
 */

_td_arena _td_create_arena(unsigned int block_size);
void _td_free_arena(_td_arena *arena);
void *_td_alloc_arena(_td_arena *arena, unsigned int size);

/**
 * End Internal Arena
 */


/**
 * Initialization
 */

int td_initialize(int width, int height);

/**
 * End Initialization
 */

#ifdef __cplusplus
}
#endif

#endif