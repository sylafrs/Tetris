#include "Video.h"

#ifndef SURFACES_H_
#define SURFACES_H_

    #include <SDL/SDL.h>
    #include "Exception.h"

    class Video;

    class Surface {
        protected:
            SDL_Surface * surface;
            Video & video;

        public:
            Surface(Video & video);
            Surface(Video & video, SDL_Surface * s);
            virtual ~Surface();

            unsigned int getWidth() const;
            unsigned int getHeight() const;

            bool fill(unsigned char r, unsigned char g, unsigned char b,
                      unsigned int x = 0, unsigned int y = 0,
                      unsigned int w = 0, unsigned int h = 0);

            bool blit(const Surface & surface,
                      unsigned int x  = 0,  unsigned int y  = 0,
                      unsigned int xx = 0,  unsigned int yy = 0,
                      unsigned int w  = 0,  unsigned int h  = 0);

            bool setKey(unsigned char r, unsigned char g, unsigned char b);

            void free();
    };

    class RectSurface : public Surface {
        public:
            RectSurface(Video & video, unsigned int w, unsigned int h) throw(Exception);
            virtual ~RectSurface();
    };

    class ImageSurface : public Surface {
        public:
            ImageSurface(Video & video, const char * path) throw(Exception);
            virtual ~ImageSurface();
    };

    class AnimSurface : public ImageSurface {
        private:
            unsigned int width;
            unsigned int cFrames;
        public:
            AnimSurface(Video & video, const char * path, unsigned int width);
            virtual ~AnimSurface();

            unsigned int getCFrames() const ;
            unsigned int getFrameWidth() const ;
    };

    bool blit(Surface & surface, const AnimSurface & anim,
              unsigned int step, unsigned int x = 0, unsigned int y = 0);

#endif//SURFACES_H_
