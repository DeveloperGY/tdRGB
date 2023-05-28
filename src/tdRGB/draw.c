#include "td.h"

void td_display()
{
    printf("\x1b[H");

    unsigned int index = 0;

    char fg_red[4];
    char fg_green[4];
    char fg_blue[4];

    char bg_red[4];
    char bg_green[4];
    char bg_blue[4];

    for (int i=0; i<TD_HEIGHT; i++)
    {
        for (int j=0; j<TD_WIDTH; j++)
        {
            // calculate colors
            snprintf(fg_red,   4, "%03d", TD_FG_COLOR_BUFFER[i*TD_WIDTH + j].red);
            snprintf(fg_green, 4, "%03d", TD_FG_COLOR_BUFFER[i*TD_WIDTH + j].green);
            snprintf(fg_blue,  4, "%03d", TD_FG_COLOR_BUFFER[i*TD_WIDTH + j].blue);

            snprintf(bg_red,   4, "%03d", TD_BG_COLOR_BUFFER[i*TD_WIDTH + j].red);
            snprintf(bg_green, 4, "%03d", TD_BG_COLOR_BUFFER[i*TD_WIDTH + j].green);
            snprintf(bg_blue,  4, "%03d", TD_BG_COLOR_BUFFER[i*TD_WIDTH + j].blue);


            // generate print buffer

            TD_PRINT_BUFFER[index++] = '\x1b';
            TD_PRINT_BUFFER[index++] = '[';
            TD_PRINT_BUFFER[index++] = '3';
            TD_PRINT_BUFFER[index++] = '8';
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = '2';
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = fg_red[0];
            TD_PRINT_BUFFER[index++] = fg_red[1];
            TD_PRINT_BUFFER[index++] = fg_red[2];
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = fg_green[0];
            TD_PRINT_BUFFER[index++] = fg_green[1];
            TD_PRINT_BUFFER[index++] = fg_green[2];
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = fg_blue[0];
            TD_PRINT_BUFFER[index++] = fg_blue[1];
            TD_PRINT_BUFFER[index++] = fg_blue[2];
            TD_PRINT_BUFFER[index++] = 'm';
            TD_PRINT_BUFFER[index++] = '\x1b';
            TD_PRINT_BUFFER[index++] = '[';
            TD_PRINT_BUFFER[index++] = '4';
            TD_PRINT_BUFFER[index++] = '8';
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = '2';
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = bg_red[0];
            TD_PRINT_BUFFER[index++] = bg_red[1];
            TD_PRINT_BUFFER[index++] = bg_red[2];
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = bg_green[0];
            TD_PRINT_BUFFER[index++] = bg_green[1];
            TD_PRINT_BUFFER[index++] = bg_green[2];
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = bg_blue[0];
            TD_PRINT_BUFFER[index++] = bg_blue[1];
            TD_PRINT_BUFFER[index++] = bg_blue[2];
            TD_PRINT_BUFFER[index++] = 'm';
            TD_PRINT_BUFFER[index++] = TD_CHAR_BUFFER[i*TD_WIDTH + j];
            TD_PRINT_BUFFER[index++] = '\x1b';
            TD_PRINT_BUFFER[index++] = '[';
            TD_PRINT_BUFFER[index++] = 'm';

            // reset buffers
            TD_CHAR_BUFFER[i*TD_WIDTH + j] = ' ';
            TD_FG_COLOR_BUFFER[i*TD_WIDTH + j] = (td_color){0, 0, 0}; // replace with clear color
            TD_BG_COLOR_BUFFER[i*TD_WIDTH + j] = (td_color){0, 0, 0}; // replace with clear color
        }
        TD_PRINT_BUFFER[index++] = '\n';
    }
    TD_PRINT_BUFFER[index - 1] = '\0';

    printf("%s", TD_PRINT_BUFFER);

    return;
}


void td_drawPoint(int x, int y, char c, td_color fgColor, td_color bgColor)
{
    if (x < 0 || x >= TD_WIDTH || y < 0 || y >= TD_HEIGHT)
    {
        return;
    }

    TD_CHAR_BUFFER[y * TD_WIDTH + x] = c;
    TD_FG_COLOR_BUFFER[y * TD_WIDTH + x] = fgColor;
    TD_BG_COLOR_BUFFER[y * TD_WIDTH + x] = bgColor;
    
    return;
}

void td_drawStrokeRect(int x, int y, unsigned int width, unsigned int height, char c, td_color fgColor, td_color bgColor)
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (i == 0 || i == height-1 || j == 0 || j == width - 1)
            {
                td_drawPoint(j+x, i+y, c, fgColor, bgColor);
            }
        }
    }
    return;
}

void td_drawFillRect(int x, int y, unsigned int width, unsigned int height, char c, td_color fgColor, td_color bgColor)
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            td_drawPoint(j+x, i+y, c, fgColor, bgColor);
        }
    }
    return;
}

void td_drawRect(int x, int y, unsigned int width, unsigned int height, char stroke, char fill, td_color strokeFGColor, td_color strokeBGColor, td_color fillFGColor, td_color fillBGColor)
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (i == 0 || i == height-1 || j == 0 || j == width - 1)
            {
                td_drawPoint(j+x, i+y, stroke, strokeFGColor, strokeBGColor);
            }
            else
            {
                td_drawPoint(j+x, i+y, fill, fillFGColor, fillBGColor);
            }
        }
    }
    return;
}

void td_drawLine(int x1, int y1, int x2, int y2, char c, td_color fgColor, td_color bgColor)
{
    float slope = (float)(y2 - y1) / (float)(x2-x1);

    if (slope >= 0)
    {
        // positive slope, +1

        if (slope > 1)
        {
            // loop y

            if (y1 > y2)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;

                temp = y1;
                y1 = y2;
                y2 = temp;
            }
            td_drawPoint(x1, y1, c, fgColor, bgColor);

            slope = 1/slope;

            float err = 0;
            float x = 0;
            
            for (int y=0; y<y2-y1; y++)
            {
                err += slope;

                if (err > 0.5)
                {
                    err--;
                    x++;
                }

                td_drawPoint(x1 + x, y1 + y, c, fgColor, bgColor);
            }
        }
        else
        {
            // loop x

            if (x1 > x2)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;

                temp = y1;
                y1 = y2;
                y2 = temp;
            }
            td_drawPoint(x1, y1, c, fgColor, bgColor);


            float err = 0;
            float y = 0;
            
            for (int x=0; x<x2-x1; x++)
            {
                err += slope;

                if (err > 0.5)
                {
                    err--;
                    y++;
                }

                td_drawPoint(x1 + x, y1 + y, c, fgColor, bgColor);
            }
        }
    }
    else
    {
        // negative slope, -1

        if (slope < -1)
        {
            // loop y

            if (y1 > y2)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;

                temp = y1;
                y1 = y2;
                y2 = temp;
            }
            td_drawPoint(x1, y1, c, fgColor, bgColor);

            slope = 1/slope;

            float err = 0;
            float x = 0;
            
            for (int y=0; y<y2-y1; y++)
            {
                err -= slope;

                if (err > 0.5)
                {
                    err--;
                    x--;
                }

                td_drawPoint(x1 + x, y1 + y, c, fgColor, bgColor);
            }
        }
        else
        {
            // loop x
            if (x1 > x2)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;

                temp = y1;
                y1 = y2;
                y2 = temp;
            }
            td_drawPoint(x1, y1, c, fgColor, bgColor);


            float err = 0;
            float y = 0;
            
            for (int x=0; x<x2-x1; x++)
            {
                err -= slope;

                if (err > 0.5)
                {
                    err--;
                    y--;
                }

                td_drawPoint(x1 + x, y1 + y, c, fgColor, bgColor);
            }
        }
    }

    return;
}

void td_drawTextHorizontal(int x, int y, const char *str, td_color fgColor, td_color bgColor)
{
    size_t len = strlen(str);

    for (int i=0; i<len; i++)
    {
        td_drawPoint(x+i, y, str[i], fgColor, bgColor);
    }

    return;
}

void td_drawTextVertical(int x, int y, const char *str, td_color fgColor, td_color bgColor)
{
    size_t len = strlen(str);

    for (int i=0; i<len; i++)
    {
        td_drawPoint(x, y+i, str[i], fgColor, bgColor);
    }

    return;
}