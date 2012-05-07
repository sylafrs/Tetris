#ifndef SDL_OBJ_H
#define SDL_OBJ_H

    #include "Video.h"
    #include "Input.h"
    #include "Exception.h"

    class SDL {

        private:
            Input in;
            Video video;

        public:
            SDL(int w, int h) throw(Exception);
            virtual ~SDL();
    };

#endif//SDL_OBJ_H
