#include "../include/SDL_Object.h"

int main() {

    SDL sdl("Tetris", 400, 300);
    Input & in = sdl.getInput();
    while(!in.quit) {


        in.update();
    }

    return 0;
}
