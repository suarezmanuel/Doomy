
// all important code is in this .cpp file, recommended to check this one first.
// which contains all the logic, and only afterward go for the definitions.

#include <iostream>
#include "../headers/mathy.h"
#include "../headers/doomy.h"
#include "../headers/draw.h"
#include <windows.h>

enum blocks {
    red, blue, green
};
int board [XBLOCKS][YBLOCKS] = {
        {red,0,0,0,0,0,0,0,0,0},
        {red,0,0,0,0,0,0,0,0,0},
        {red,0,0,0,0,0,0,red,0,0},
        {red,0,0,0,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,red,red,red,red,red,red,0,0,0}
};

void drawBoard (SDL_Renderer *&renderer) {
    for (int i = 0; i < BLOCKSONSCREENWIDTH; i++)
    {
        for (int j = 0; j < BLOCKSONSCREENHEIGHT; j++)
        {
            SDL_Rect rectToFill; rectToFill.h = BLOCKHEIGHT; rectToFill.w = BLOCKWIDTH;
            rectToFill.x = i*BLOCKWIDTH; rectToFill.y = j*BLOCKHEIGHT;  

            SDL_Color drawColor;
            if (board[i][j]) {drawColor = {255,255,255,255};}
            else {drawColor = {0,0,0,255};}

            SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
            SDL_RenderFillRect(renderer, &rectToFill);
        }
    }
    
}

void drawGrid (SDL_Renderer *renderer, SDL_Color color) {

    enum Coords {
        X, Y
    };

    int p1 [2] = {0,0};
    int p2 [2] = {0,0};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // ------ draw rows -----------
    p1[X] = 0;
    p2[X] = SCREENWIDTH;

    for (size_t i = 0; i < BLOCKSONSCREENHEIGHT; i++)
    {
        p1[Y] = p2[Y] = i*BLOCKHEIGHT;

        SDL_RenderDrawLine(renderer, p1[X], p1[Y], p2[X], p2[Y]);
    }
    

    // ------ draw cols -----------
    p1[Y] = 0;
    p2[Y] = SCREENHEIGHT;
    
    for (size_t i = 0; i < BLOCKSONSCREENWIDTH; i++)
    {
        p1[X] = p2[X] = i*BLOCKWIDTH;

        SDL_RenderDrawLine(renderer, p1[X], p1[Y], p2[X], p2[Y]);
    }
}

int main (int argc, char* argv[]) {
    
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, 0, &window, &renderer);   

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }

    // inits as struct, idk why I chose it like this
    point player {SCREENWIDTH/2 - (BLOCKWIDTH/2), SCREENHEIGHT/2 - (BLOCKHEIGHT/2)};
    // draw grid on screen
    SDL_Color gridColor{70,70,40,255};
    drawGrid(renderer, gridColor);

    SDL_RenderPresent(renderer);

    // draw_player();
    // draw_player_dir();
    SDL_Color color {0,0,255,255};

    SDL_SetRenderDrawColor(renderer, 50,50,200,255);
    fillCircle(renderer, player[0], player[1], 10);
    SDL_RenderPresent(renderer);

    color = {255,0,0,255};
    // inits as struct, idk why I chose it like this
    cast_rays(player);
    for (int i = 0; i < FOV_RADIUS_IN_BLOCKS; ++i) {
        step_and_draw_all(renderer);
        Sleep(100);
    }

    SDL_RenderPresent(renderer);
    
    SDL_Event windowEvent;
    bool running = true;

    while (running) {

        if (SDL_PollEvent(&windowEvent)) {
            
            switch (windowEvent.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
    }
    return 0;
}