#include "../include/Music.h"
#include "../include/Exception.h"

#include <SDL/SDL_mixer.h>
#include <string>

using namespace std;

Music::Music(const string & path) throw(Exception) {
    this->music = Mix_LoadMUS(path.c_str());
    if(this->music == NULL) {
        throw(Exception(string("Erreur lors du chargement de la musique\n") + Mix_GetError()));    
    }
}

Music::~Music() {
    if(this->music != NULL) {
        Mix_FreeMusic(music);
    }
}
