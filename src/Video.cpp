#include "../include/Video.h"
#include "../include/Exception.h"
#include <string>
#include <SDL/SDL.h>

using namespace std;

Video::Video(int w, int h) throw(Exception) {
    this->ecran = SDL_SetVideoMode(w, h, 8*sizeof(int), SDL_HWSURFACE);
    if(this->ecran == NULL) {
        throw Exception(string("Problème lors de l'initialisation de la fenetre\n") + SDL_GetError());
    }
}

Video::~Video() {

}

void Video::setTitle(const string & title) {
    SDL_WM_SetCaption(title.c_str(), NULL);
}


