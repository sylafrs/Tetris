#include "Video.h"
#include "Exception.h"
#include <string>
#include <SDL/SDL.h>

using namespace std;

Video::Video(int w, int h) throw(Exception) {
    if(SDL_SetVideoMode(w, h, 8*sizeof(int), SDL_HWSURFACE) == NULL) {
        throw Exception(string("Problème lors de l'initialisation de la fenetre\n") + SDL_GetError());
    }
}

Video::~Video() {

}


