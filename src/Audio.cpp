#include "../include/Audio.h"
#include "../include/Exception.h"

#include <SDL/SDL_mixer.h>
#include <string>

using namespace std;

Audio::Audio() throw(Exception) {
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        throw(Exception(string("Problème lors de l'initialisation de SDL_Mixer\n") + Mix_GetError()));
   }
}

Audio::~Audio() {
    Mix_CloseAudio();
}
