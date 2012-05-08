#ifndef VIDEO_H_
#define VIDEO_H_

    #include <SDL/SDL.h>
    #include <string>
    #include "Exception.h"
    #include "Surface.h"

    class Video : public Surface {

        public:
            Video(int w, int h) throw(Exception);
            virtual ~Video();

            void setTitle(const std::string & title);
            const SDL_PixelFormat* getFormat() const;

            bool flip();
    };

#endif//VIDEO_H_
