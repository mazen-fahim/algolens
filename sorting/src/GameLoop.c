#include <SDL2/SDL.h>
#include "../include/GamePhysics.h"
#include "../include/Draw.h"
#include "../include/globals.h"
#include "../include/HandleEvents.h"

void startGame(void)
{
    SDL_Event event;
    bool quit = false;
    Uint32 lastTick = SDL_GetTicks();
    Uint32 currentTick = 0;
    Uint32 diff = 0;
    float elapsed = 0;
    while(!quit){

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        currentTick = SDL_GetTicks();
        diff = currentTick - lastTick;
        elapsed = diff / 1000.0f;
        update(elapsed);
        draw();
        lastTick = currentTick;
    }
}

