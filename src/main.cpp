#include "../include/SDL_Object.h"
#include "../include/constantes.h"
#include "../include/shapes.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Shape.h"
#include "../include/Structure.h"
#include "../include/Unit.h"
#include "../include/Random.h"

#include <iostream>


using namespace std;

#ifndef __LINUX__
int main(int argc, char * argv[]) {
#else
int main() {
#endif

    try {
        SDL sdl(windowTitle, windowWidth, windowHeight);
        Input & in = sdl.getInput();    // Inputs
        Video & video = sdl.getVideo(); // Screen

        {
            ImageSurface fond(video, "imgs/fond.bmp");
            video.blit(fond);
        }

        RectSurface gameZone(video, squareSize*wGrid, squareSize*hGrid);
        ImageSurface rouge (video, "imgs/rouge.bmp");
        ImageSurface bleu  (video, "imgs/bleu.bmp");
        ImageSurface vert  (video, "imgs/vert.bmp");
        ImageSurface jaune (video, "imgs/jaune.bmp");
        ImageSurface orange(video, "imgs/orange.bmp");
        ImageSurface cyan  (video, "imgs/cyan.bmp");
        ImageSurface violet(video, "imgs/violet.bmp");

        unsigned int arraySize = 7;
        Shape array[] = {
            Shape(jaune,  oShape, sO, cO, xInitO, yInitO),
            Shape(cyan,   iShape, sI, cI, xInitI, yInitI),
            Shape(rouge,  zShape, sZ, cZ, xInitZ, yInitZ),
            Shape(vert,   sShape, sS, cS, xInitS, yInitS),
            Shape(violet, tShape, sT, cT, xInitT, yInitT),
            Shape(bleu,   jShape, sJ, cJ, xInitJ, yInitJ),
            Shape(orange, lShape, sL, cL, xInitL, yInitL)
        };

        Structure structure;
        Random rand;
        Unit unit(structure, array[rand.next(0, arraySize-1)]);

        bool keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT] && !in.key[SDLK_a] && !in.key[SDLK_d]);
        Chrono fall, key;

        gameZone.fill(0, 0, 0);
        blit(gameZone, unit);
        blit(gameZone, structure);
        video.blit(gameZone);

        sdl.update(30);
        bool lose = false;
        while(!in.quit && !in.key[SDLK_ESCAPE] && !lose) {

            if(fall.check(1000)) {
                if(!unit.bottom()) {
                    structure.add(unit);
                    unit.change(array[rand.next(0, arraySize-1)]);
                    if(structure.check(unit)) {
                        lose = true;
                    }
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
            blit(gameZone, structure);
            video.blit(gameZone);
            sdl.update(30);
        }
    }
    catch(const Exception & e) {
        cerr << e << endl;
    }

    return 0;
}
