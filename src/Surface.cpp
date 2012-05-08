#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Exception.h"
#include <SDL/SDL.h>
#include <string>
#include <iostream>

using namespace std;

Surface::Surface(Video & video) : video(video) {
    this->surface = NULL;
}

Surface::Surface(Video & video, SDL_Surface * surface) : video(video) {
    this->surface = surface;
}

Surface::~Surface() {
    if(this->surface != NULL) {
        SDL_FreeSurface(this->surface);
    }
    this->surface = NULL;
}

RectSurface::RectSurface(Video & video, unsigned int w, unsigned int h) throw(Exception) : Surface(video) {
    this->surface = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, sizeof(int)*8, 0, 0, 0, 0);
    if(this->surface == NULL) {
        throw Exception(string("Erreur lors de la création d'une surface (rectangle)\n") + SDL_GetError());
    }
}

RectSurface::~RectSurface() {
    
}

unsigned int Surface::getWidth() const {
    return this->surface->w;
}

unsigned int Surface::getHeight() const {
    return this->surface->h;
}

bool Surface::fill( unsigned char r, unsigned char g, unsigned char b, 
                    unsigned int x, unsigned int y, unsigned int w, unsigned int h) {

    if(this->surface == NULL) {
        return false;
    }

    int pixel = SDL_MapRGB(video.getFormat(), r, g, b);

    if(x == 0 && y == 0 && w == 0 && h == 0) {
        return (SDL_FillRect(this->surface, NULL, pixel) == 0);
    }

    if(w == 0) {
        w = this->surface->w;
    }

    if(h == 0) {
        h = this->surface->h;
    }

    SDL_Rect rect = {x, y, w, h};    
    return (SDL_FillRect(this->surface, &rect, pixel) == 0);
}

bool Surface::blit(const Surface & surface, unsigned int x, unsigned int y, 
                   unsigned int xx, unsigned int yy, unsigned int w, unsigned int h) {

    if(w == 0) {
        w = surface.surface->w;
    }
    if(h == 0) {
        h = surface.surface->h;
    }

    SDL_Rect srcrect = {xx, yy, w, h};
    SDL_Rect dstrect = {x, y, 0, 0};
    
    return (SDL_BlitSurface(surface.surface, &srcrect, this->surface, &dstrect) == 0);    
}

