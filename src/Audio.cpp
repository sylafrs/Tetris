#include "../include/Audio.h"
#include "../include/Exception.h"

#include <SDL/SDL_mixer.h>
#include <string>

using namespace std;

Audio::Audio() throw(Exception) : cChannels(0) {
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        throw(Exception(string("Problème lors de l'initialisation de SDL_Mixer\n") + Mix_GetError()));
   }
}

Audio::~Audio() {
    this->haltSounds();
    Mix_CloseAudio();
}

unsigned int Audio::createChannel() throw(Exception) {

    if(Mix_AllocateChannels((int)this->cChannels+1) != (int)this->cChannels+1) {
        throw(Exception(string("Problème lors de l'allocation de chaîne SDL_mixer\n")+Mix_GetError()));
    }
    this->cChannels = this->cChannels + 1;
    
    return this->cChannels-1;
}

void Audio::haltSounds() {
    Mix_HaltChannel(-1);
}

