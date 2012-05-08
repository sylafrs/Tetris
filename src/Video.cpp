#include "../include/Video.h"
#include "../include/Exception.h"
#include <string>
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

Video::Video(int w, int h) throw(Exception) : Surface(*this) {
    this->surface = SDL_SetVideoMode(w, h, 8*sizeof(int), SDL_HWSURFACE);
    if(this->surface == NULL) {
        throw Exception(string("Problème lors de l'initialisation de la fenetre\n") + SDL_GetError());
    }
}

Video::~Video() {

}

void Video::setTitle(const string & title) {
    SDL_WM_SetCaption(title.c_str(), NULL);
}

const SDL_PixelFormat* Video::getFormat() const {
    return this->surface->format;
}

bool Video::flip() {
    return (SDL_Flip(this->surface) == 0);
}

