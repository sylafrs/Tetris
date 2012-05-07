#include "Input.h"
#include <SDL/SDL.h>


Input::Input() {
    memset(this, 0, sizeof(*this));
}

Input::~Input() {

}

void Input::update() {
    SDL_Event event;

    this->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
    this->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                this->key[event.key.keysym.sym]=1;
            break;
            case SDL_KEYUP:
                this->key[event.key.keysym.sym]=0;
            break;
            case SDL_MOUSEMOTION:
                this->mousex    = event.motion.x;
                this->mousey    = event.motion.y;
                this->mousexrel = event.motion.xrel;
                this->mouseyrel = event.motion.yrel;
            break;
            case SDL_MOUSEBUTTONDOWN:
                this->mousebuttons[event.button.button]=1;
            break;
            case SDL_MOUSEBUTTONUP:
                if( event.button.button!=SDL_BUTTON_WHEELUP && 
                    event.button.button!=SDL_BUTTON_WHEELDOWN )
                {
                    this->mousebuttons[event.button.button]=0;
                }
            break;
            case SDL_QUIT:
                quit = 1;
            break;
            default:
            break;
        }
    }
}

