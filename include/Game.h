#ifndef GAME_H_
#define GAME_H_

    #include "Exception.h"
    #include "SDL_Object.h"
    #include "Surface.h"
    #include "Shape.h"
    #include "Sound.h"
    #include "Music.h"
    #include <vector>
    #include <string>

    typedef void (*changeSpeedFct)(unsigned int &);

    class Game {
        private:
            SDL & sdl;

            unsigned int xGrid, yGrid, wGrid, hGrid, squareSize;
            unsigned int wNext, hNext, xNext, yNext, initX, initY;
            unsigned int xStore, yStore;
            unsigned int fallSpeedInit, fastFallSpeed, moveSpeed;
            unsigned int minFrameTime; // = 60/maxFPS

            changeSpeedFct changeSpeed;

            std::vector<const Shape *> shapeArray;
            Surface * empty;

            const Sound * boomSnd;
            const AnimSurface * boom;
            unsigned int disappearFrame;
            unsigned int animSpeed;

            const Music * music;

            const AnimSurface * digits;
            unsigned int xCLines, yCLines, digitsSpace, cDigits;

        public:
            Game(SDL & sdl) throw(Exception);
            virtual ~Game();

            void setStoreCoords(unsigned int x, unsigned int y);
            void setGridCoords(unsigned int x, unsigned int y);
            void setGridSize(unsigned int w, unsigned int h);
            void setNextCoords(unsigned int x, unsigned int y);
            void setNextSize(unsigned int w, unsigned int h);
            void setSquareSize(unsigned int s);
            void setInitCoords(unsigned int x, unsigned int y);
            void setChangeSpeedFunction(changeSpeedFct changeSpeed);
            void setSpeedInit(unsigned int speed);
            void setFastSpeed(unsigned int speed);
            void setMoveSpeed(unsigned int speed);
            void setMaxFPS(unsigned int fps);
            void setCLinesPos(unsigned int x, unsigned int y);
            void setCLinesDigits(unsigned int space, unsigned int count);

            void setEmpty(const std::string & image) throw(Exception);
            void setBackground(const std::string & image) throw(Exception);
            void setBoomAnimation(const std::string & image, unsigned int width,
                                  unsigned int disappearFrame, unsigned int animSpeed);

            void addShape(const Surface & surf, const shape & shapeShape,
                          unsigned int size, unsigned int count,
                          unsigned int initX, unsigned int initY ) throw(Exception) ;

            void setBoomSound(const std::string & sound) throw(Exception);
            void setMusic(const std::string & music) throw(Exception);
            void setDigits(const std::string & path, unsigned int width) throw(Exception);

            void menu() throw(Exception);
            void play() throw(Exception);
    };

#endif//GAME_H_
