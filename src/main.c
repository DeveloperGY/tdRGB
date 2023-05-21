#include <td.h>

int main(void)
{
    const int width = 40;
    const int height = 24;

    td_color c0 = {150, 0, 150};
    td_color c1 = {135, 192, 60};

    if (!td_init(width, height))
    {
        return -1;
    }

    for (int i=0; i<60; i++)
    {
        td_drawPoint(0, 0, '#', c0, c1);
        td_drawPoint(width - 1, height - 1, '#', c1, c0);
        td_drawLine(0, 0, width-1, height-1, '-', c0, c1);
        td_display();
    }
    td_terminate(0);

    return 0;
}