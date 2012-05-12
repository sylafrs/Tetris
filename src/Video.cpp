#include "../include/Video.h"
#include "../include/Exception.h"
#include <string>
#include <SDL/SDL.h>

using namespace std;

Video::Video(int w, int h) : w(w), h(h), Surface(*this) {

}

void Video::init() throw(Exception) {
    this->surface = SDL_SetVideoMode(this->w, this->h, 8*sizeof(int), SDL_HWSURFACE);
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

