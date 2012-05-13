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
        Mix_HaltMusic();
        Mix_FreeMusic(music);
    }
}

void Music::infinityPlay() const throw(Exception) {
    this->play(-1);
}

void Music::play(int loops) const throw(Exception) {
    if(Mix_PlayMusic(this->music, loops) == -1) {
        throw(Exception(string("Erreur lors de la lecture de la musique\n")+Mix_GetError()));
    }
}

void Music::play() const throw(Exception) {
    this->play(1);
}

bool Music::paused() const {
    return (Mix_PausedMusic() == 1);
}

void Music::resume() const {
    Mix_ResumeMusic();
}

void Music::pause() const {
    Mix_PauseMusic();
}

void Music::rewind() const {
    Mix_RewindMusic();
}

void Music::halt() const {
    Mix_HaltMusic();
}

