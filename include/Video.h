#ifndef VIDEO_H_
#define VIDEO_H_

    #include <SDL/SDL.h>
    #include <string>
    #include "Exception.h"
    #include "Surface.h"

    class Video : public Surface {

        private:
            int w;
            int h;

        public:
            Video(int w, int h);
            virtual ~Video();

            void init() throw(Exception);

            void setTitle(const std::string & title);
            const SDL_PixelFormat* getFormat() const;

            bool flip();
    };

#endif//VIDEO_H_
