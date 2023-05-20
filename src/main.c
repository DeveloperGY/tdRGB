#include <td.h>

#include <stdio.h>

int main(void)
{
    _td_arena arena = _td_create_arena(1024);

    int *arr = _td_alloc_arena(&arena, 16 * sizeof(int));

    _td_free_arena(&arena);

    printf("\x1b[48;2;170;000;200m \x1b[0m");

    return 0;
}