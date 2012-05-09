#include "../include/SDL_Object.h"
#include "../include/constantes.h"
#include "../include/shapes.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Shape.h"
#include "../include/Structure.h"
#include "../include/Unit.h"

#include <iostream>
#include <ctime>

int getRand(int min, int max) {
    //return (int)(rand()/(double)RAND_MAX*(max-min))+min;
    return rand()%(max-min+1)+min;
}

using namespace std;

#ifndef __LINUX__
int main(int argc, char * argv[]) {
#else
int main() {
#endif

    srand(time(NULL));

    try {
        // Initializes the SDL
        SDL sdl(windowTitle, windowWidth, windowHeight);
        Input & in = sdl.getInput();    // Inputs
        Video & video = sdl.getVideo(); // Screen

        // Surfaces
        RectSurface gameZone(video, squareSize*wGrid, squareSize*hGrid);
        RectSurface rouge(video, squareSize, squareSize);
        rouge.fill(255, 0, 0);

        // Shapes
        unsigned int arraySize = 7;
        Shape array[] = {
            Shape(rouge, squareShape, sSquare, cSquare, xInitSquare, yInitSquare),
            Shape(rouge, lineShape, sLine, cLine, xInitLine, yInitLine),
            Shape(rouge, zShape, sZ, cZ, xInitZ, yInitZ),
            Shape(rouge, zShape, sS, cS, xInitS, yInitS),
            Shape(rouge, tShape, sT, cT, xInitT, yInitT),
            Shape(rouge, largeLShape, sLargeL, cLargeL, xInitLargeL, yInitLargeL),
            Shape(rouge, longLShape, sLongL, cLongL, xInitLongL, yInitLongL)
        };

        Structure structure;
        Unit unit(structure, array[getRand(0, arraySize-1)]);

        bool keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT] && !in.key[SDLK_a] && !in.key[SDLK_d]);
        Chrono fall, key;

        gameZone.fill(0, 0, 0);
        blit(gameZone, unit);

        video.fill(255, 255, 255);
        video.blit(gameZone);

        sdl.update(30);
        while(!in.quit && !in.key[SDLK_ESCAPE]) {

            if(fall.check(1000)) {
                if(!unit.bottom()) {
                    structure.add(unit);
                    unit.change(array[getRand(0, arraySize-1)]);
                }
                fall.reset();
            }

            if((in.key[SDLK_DOWN] || in.key[SDLK_s]) && fall.check(50)) {
                unit.bottom();
            }

            if(keyup || key.check(300)) {
                key.reset();
                if(in.key[SDLK_LEFT] || in.key[SDLK_a]) {
                    unit.left();
                }
                if(in.key[SDLK_RIGHT] || in.key[SDLK_d]) {
                    unit.right();
                }
            }

            keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT] && !in.key[SDLK_a] && !in.key[SDLK_d]);

            if(in.key[SDLK_UP] || in.key[SDLK_w]) {
                in.key[SDLK_UP] = in.key[SDLK_w] = false;
                unit.rotate();
            }

            if(in.key[SDLK_SPACE]) {
                in.key[SDLK_SPACE] = false;
            }

            gameZone.fill(0, 0, 0);
            blit(gameZone, unit);
            video.fill(255, 255, 255);
            video.blit(gameZone);
            sdl.update(30);
        }
    }
    catch(Exception e) {
        cerr << e << endl;
    }

    return 0;
}
