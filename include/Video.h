#ifndef VIDEO_H_
#define VIDEO_H_

    #include <SDL/SDL.h>
    #include <string>
    #include "Exception.h"

    class Video {

        private:
            SDL_Surface * ecran;

        public:
            Video(int w, int h) throw(Exception);
            virtual ~Video();

            void setTitle(const std::string & title);
    };

#endif//VIDEO_H_
