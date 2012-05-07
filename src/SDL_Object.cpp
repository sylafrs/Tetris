#include "../include/SDL_Object.h"
#include "../include/Video.h"
#include "../include/Input.h"
#include "../include/Exception.h"
#include <SDL/SDL.h>
#include <string>

using namespace std;

SDL::SDL(const string & title, int w, int h) throw(Exception) : video(w, h) {
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        throw Exception(string("Problème lors de l'initialisation de la SDL\n") + SDL_GetError());
    }    

    video.setTitle(title);
}

SDL::~SDL() {
    SDL_Quit();
}

Input & SDL::getInput() {
    return this->in;
}
