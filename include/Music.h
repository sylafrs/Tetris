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
            
            void infinityPlay() const throw(Exception);
            void play(int loops) const throw(Exception);
            void play() const throw(Exception);
            
            bool paused() const ;
            void resume() const ;
            void pause() const ;
            void rewind() const ;
            void halt() const ;
    };

#endif//MUSIC_H_
