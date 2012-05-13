#include "../include/Exception.h"
#include "../include/Sound.h"
#include "../include/Audio.h"

#include <SDL/SDL_mixer.h>
#include <string>

using namespace std;

Sound::Sound(Audio & audio, const string & path) throw(Exception) {
    this->channel = audio.createChannel();
    this->sound = Mix_LoadWAV(path.c_str());
    if(this->sound == NULL) {
        throw(Exception(string("Erreur lors de l'allocation du son ")+path+'\n'+Mix_GetError()));
    }
}

Sound::~Sound() {
    this->halt();
    Mix_FreeChunk(this->sound);
}

void Sound::infinityPlay() const throw(Exception) {
    this->play(-1);
}

void Sound::play(int loops) const throw(Exception) {
    if(Mix_PlayChannel(this->channel, this->sound, loops) == -1) {
        throw(string("Erreur lors de la lecture d'un son\n")+Mix_GetError());
    }
}

void Sound::play() const throw(Exception) {
    this->play(0);
}

bool Sound::paused() const {
    return Mix_Paused(this->channel) == 1;
}

void Sound::resume() const {
    Mix_Resume(this->channel);
}

void Sound::pause() const {
    Mix_Pause(this->channel);
}

void Sound::halt() const {
    Mix_HaltChannel(this->channel);
}


