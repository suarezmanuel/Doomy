
// all important code is in this .cpp file, recommended to check this one first.
// which contains all the logic, and only afterward go for the definitions.

#include <iostream>
#include "headers/mathy.h"
#include "headers/doomy.h"


int main (int argc, char* argv[]) {
    
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, 0, &window, &renderer);   

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }

    // inits as struct, idk why I chose it like this
    point starting_pos {SCREENWIDTH/2, SCREENHEIGHT/2};
    cast_rays(starting_pos);
    for (int i = 0; i < FOVRADIUS; ++i) {
        step_and_draw_all(renderer);
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