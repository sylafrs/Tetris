#ifndef SDL_OBJ_H
#define SDL_OBJ_H

    #include "Video.h"
    #include "Audio.h"
    #include "Input.h"
    #include "Exception.h"
    #include <string>

    class SDL {

        private:    
            Input in;
            Video video;
            Audio audio;
       
        public:
            SDL(const std::string & title, int w, int h) throw(Exception);
            virtual ~SDL();

            Input & getInput();
            Video & getVideo();
            Audio & getAudio();

            bool update();
    };

#endif//SDL_OBJ_H
