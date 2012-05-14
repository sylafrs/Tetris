#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Exception.h"
#include "../include/SDL/SDL.h"
#include <string>

using namespace std;

Surface::Surface(Video & video) : video(video) {
    this->surface = NULL;
}

Surface::Surface(Video & video, SDL_Surface * surface) : video(video) {
    this->surface = surface;
}

Surface::~Surface() {

}

void Surface::free() {
    if(this->surface != NULL) {
        SDL_FreeSurface(this->surface);
    }
    this->surface = NULL;
}

RectSurface::RectSurface(Video & video, unsigned int w, unsigned int h) throw(Exception) : Surface(video) {
    this->surface = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, sizeof(int)*8, 0, 0, 0, 0);
    if(this->surface == NULL) {
        string str("Erreur lors de la création d'une surface (rectangle)\n");
        str += SDL_GetError();
        throw Exception(str);
    }
}

RectSurface::~RectSurface() {
    this->free();
}

ImageSurface::ImageSurface(Video & video, const char * path) throw(Exception) : Surface(video) {
    this->surface = SDL_LoadBMP(path);
    if(this->surface == NULL) {
        throw Exception(string("Erreur lors du chargement de l'image : ") + path + '\n' + SDL_GetError());
    }
}

ImageSurface::~ImageSurface() {
    this->free();
}

AnimSurface::AnimSurface(Video & video, const char * path, unsigned int width) :
ImageSurface(video, path), width(width){
    this->cFrames = this->surface->w/width;
}

AnimSurface::~AnimSurface() {

}

unsigned int AnimSurface::getFrameWidth() const {
    return this->width;
}

bool blit(Surface & surface, const AnimSurface & anim, unsigned int step, unsigned int x, unsigned int y) {

    if(step >= anim.getCFrames()) {
        return false;
    }

    unsigned int w = anim.getFrameWidth();
    unsigned int h = anim.getHeight();

    return surface.blit(
        anim,
        x, y,
        w*step, 0,
        w, h
    );
}

unsigned int AnimSurface::getCFrames() const {
    return this->cFrames;
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

bool Surface::setKey(unsigned char r, unsigned char g, unsigned char b) {
    int color = SDL_MapRGB(this->surface->format, r, g, b);
    return (SDL_SetColorKey(this->surface, SDL_SRCCOLORKEY, color) == 0);
}

