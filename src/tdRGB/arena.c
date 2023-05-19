#include "td.h"

_td_arena _td_create_arena(unsigned int block_size)
{
    unsigned int size = 0;
    void *block = (void *)malloc(block_size);

    if (block != NULL)
    {
        size = block_size;
    }

    return (_td_arena){block, 0, size};
}

void _td_free_arena(_td_arena *arena)
{
    arena->pointer = 0;
    arena->size = 0;

    if (arena->block != NULL)
    {
        free(arena->block);
    }

    return;
}

void *_td_alloc_arena(_td_arena *arena, unsigned int size)
{
    if (size > arena->size - arena->pointer)
    {
        return NULL;
    }

    arena->pointer += size;

    return arena->block + (arena->pointer - size);
}