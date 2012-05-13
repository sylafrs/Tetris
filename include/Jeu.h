#ifndef JEU_H_
#define JEU_H_

    #include "Exception.h"
    #include "SDL_Object.h"
    #include "Surface.h"
    #include "Shape.h"
    #include <vector>
    #include <string>

    typedef void (*changeSpeedFct)(unsigned int &);

    class Jeu {
        private:
            SDL & sdl;

            unsigned int xGrid, yGrid, wGrid, hGrid, squareSize;
            unsigned int wNext, hNext, xNext, yNext, initX, initY;
            unsigned int fallSpeedInit, fastFallSpeed, moveSpeed;
            unsigned int minFrameTime; // = 60/maxFPS

            changeSpeedFct changeSpeed;
            std::vector<const Shape *> shapeArray;
            Surface * empty;

        public:
            Jeu(SDL & sdl) throw(Exception);
            virtual ~Jeu();

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

            void setEmpty(std::string image) throw(Exception);
            void setBackground(std::string image) throw(Exception);

            void addShape(const Surface & surf, const shape & shapeShape,
                          unsigned int size, unsigned int count,
                          unsigned int initX, unsigned int initY ) throw(Exception) ;

            void play() throw(Exception);
    };

#endif//JEU_H_
