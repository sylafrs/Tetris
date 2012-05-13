#ifndef MUSIC_H_
#define MUSIC_H_

    #include "Exception.h"

    #include <SDL/SDL_mixer.h>
    #include <string>

    class Music {
        private:
            Mix_Music *music;
            
        public:
            Music(const std::string & path) throw(Exception);
            virtual ~Music();
    };

#endif//MUSIC_H_
