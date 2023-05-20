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

/**
 * End Struct Definitions
 */


/**
 * Globals
 */

// Used for allocation of tdrgb buffers
extern _td_arena _TD_ARENA;

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


#ifdef __cplusplus
}
#endif

#endif