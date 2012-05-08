#ifndef SDL_OBJ_H
#define SDL_OBJ_H

    #include "Video.h"
    #include "Input.h"
    #include "Exception.h"
    #include "Chrono.h"
    #include <string>

    class SDL {

        private:    
            Input in;
            Video video;
            Chrono chrono;
       
        public:
            SDL(const std::string & title, int w, int h) throw(Exception);
            virtual ~SDL();

            Input & getInput();
            Video & getVideo();

            bool update(Uint32 delay);
    };

#endif//SDL_OBJ_H
