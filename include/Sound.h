#ifndef SOUND_H_
#define SOUND_H_

    #include "Exception.h"
    #include "Audio.h"

    #include <SDL/SDL_mixer.h>
    #include <string>

    class Sound {
        private:
            Mix_Chunk * sound;
            unsigned int channel;
                        
        public:
            Sound(Audio & audio, const std::string & path) throw(Exception);
            virtual ~Sound();
            
            void infinityPlay() const throw(Exception);
            void play(int loops) const throw(Exception);
            void play() const throw(Exception);
            
            bool paused() const ;
            void resume() const ;
            void pause() const ;
            void halt() const ;
            
    };

#endif//SOUND_H_
