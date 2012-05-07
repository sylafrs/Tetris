#ifndef VIDEO_H_
#define VIDEO_H_

    #include <SDL/SDL.h>
    #include "Exception.h"

    class Video {

        public:
            Video(int w, int h) throw(Exception);
            virtual ~Video();

    };

#endif//VIDEO_H_
