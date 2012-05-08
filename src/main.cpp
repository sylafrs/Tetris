#include "../include/SDL_Object.h"
#include "../include/constantes.h"
#include "../include/shapes.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Shape.h"
#include <iostream>

using namespace std;

int main() {
   
    try {
        SDL sdl(windowTitle, windowWidth, windowHeight);
        Input & in = sdl.getInput();
        Video & video = sdl.getVideo();

        RectSurface rouge(video, squareSize, squareSize);
        rouge.fill(255, 0, 0);
 
        Shape array[] = {
            Shape(rouge, squareShape, sSquare, cSquare, xInitSquare, yInitSquare),
            Shape(rouge, lineShape, sLine, cLine, xInitLine, yInitLine),
            Shape(rouge, zShape, sZ, cZ, xInitZ, yInitZ),
            Shape(rouge, zShape, sS, cS, xInitS, yInitS),
            Shape(rouge, tShape, sT, cT, xInitT, yInitT),
            Shape(rouge, largeLShape, sLargeL, cLargeL, xInitLargeL, yInitLargeL),
            Shape(rouge, longLShape, sLongL, cLongL, xInitLongL, yInitLongL)
        };

        unsigned int arraySize = 7;
    
        Chrono tombee, touche;
        Shape * unit = &array[3];
        unsigned int x = 0, y = 0;

        video.fill(255, 255, 255);
        blitInit(video, *unit, x, y);
        sdl.update(30);

        bool relache = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT]);
        int form = 0;
        int cForms = unit->getCForms();

        while(!in.quit) {
            
            if(tombee.check(1000) || (in.key[SDLK_DOWN] && tombee.check(50))) {
                tombee.reset();  
                y++;              
            }

            if(relache || touche.check(300)) {
                touche.reset();
                if(in.key[SDLK_LEFT]) {
                    x--;
                }
                if(in.key[SDLK_RIGHT]) {
                    x++;
                }
            }

            relache = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT]);

            if(in.key[SDLK_SPACE]) {
                in.key[SDLK_SPACE] = false;
                form++;
                if(form >= cForms) {
                    form = 0;
                }
            }

            video.fill(255, 255, 255);
            blit(video, *unit, x, y, form);
            sdl.update(30);
        }
    }
    catch(Exception e) {
        cerr << e << endl;
    }

    return 0;
}
