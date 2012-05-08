#include "../include/Chrono.h"
#include <SDL/SDL.h>
            
Chrono::Chrono() {
    reset();
}

bool Chrono::check(Uint32 delay) {
    Uint32 now = SDL_GetTicks();
    return (now-prevTime > delay);
}

void Chrono::wait(Uint32 delay) {
    if(!check(delay)) {
        Uint32 now = SDL_GetTicks();
        SDL_Delay((prevTime+delay)-now);        
    }
    reset();
}

void Chrono::reset() {
    prevTime = SDL_GetTicks();
}
