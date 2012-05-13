#include "../include/SDL_Object.h"
#include "../include/Video.h"
#include "../include/Input.h"
#include "../include/Exception.h"
#include <SDL/SDL.h>
#include <string>

using namespace std;

SDL::SDL(const string & title, int w, int h) throw(Exception) : video(w, h), audio() {
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1) {
        throw Exception(string("Problème lors de l'initialisation de la SDL\n") + SDL_GetError());
    }

    this->video.init();
    this->video.setTitle(title);
}

SDL::~SDL() {
    SDL_Quit();
}

Input & SDL::getInput() {
    return this->in;
}

Video & SDL::getVideo() {
    return this->video;
}

Audio & SDL::getAudio() {
    return this->audio;
}

bool SDL::update() {
    this->in.update();
    return this->video.flip();
}
