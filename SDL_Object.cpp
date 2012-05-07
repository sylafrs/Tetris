#include "SDL_Object.h"
#include "Video.h"
#include "Input.h"
#include "Exception.h"
#include <SDL/SDL.h>
#include <string>

using namespace std;

SDL::SDL(int w, int h) throw(Exception) : video(w, h) {
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        throw Exception(string("Problème lors de l'initialisation de la SDL\n") + SDL_GetError());
    }    
}

SDL::~SDL() {
    SDL_Quit();
}
