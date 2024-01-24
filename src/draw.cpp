#include "headers/draw.h"

void putPixel (SDL_Renderer* &renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void drawCircle(SDL_Renderer* &re, int x0, int y0, int radius)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        putPixel(re, x0 + x, y0 + y);
        putPixel(re, x0 + y, y0 + x);
        putPixel(re, x0 - y, y0 + x);
        putPixel(re, x0 - x, y0 + y);
        putPixel(re, x0 - x, y0 - y);
        putPixel(re, x0 - y, y0 - x);
        putPixel(re, x0 + y, y0 - x);
        putPixel(re, x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void fillCircle (SDL_Renderer* &re, int x0, int y0, int radius) {
    for (int i = radius; i >= 0; i--)
    {
        drawCircle(re, x0, y0, i);
    }
    
}