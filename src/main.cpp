#include "../include/SDL_Object.h"
#include "../include/constantes.h"
#include "../include/shapes.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Shape.h"
#include <iostream>
#include <ctime>

int getRand(int min, int max) {
    return (int)((double)rand()/RAND_MAX*(max-min))+min;    
}

using namespace std;

int main() {

    srand(time(NULL));
   
    try {
        // Initializes the SDL
        SDL sdl(windowTitle, windowWidth, windowHeight);
        Input & in = sdl.getInput();    // Inputs
        Video & video = sdl.getVideo(); // Screen

        // Surfaces
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
            
        
        Shape * unit = &array[getRand(0, arraySize-1)];
        unsigned int x = initX, y = initY;
        int form = 0;
        int cForms = unit->getCForms();
     
        bool keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT]);
        Chrono fall, key;
        
        video.fill(255, 255, 255);
        blitInit(video, *unit, x, y);
        sdl.update(30);
        while(!in.quit && !in.key[SDLK_ESCAPE]) {
            
            if(fall.check(1000) || (in.key[SDLK_DOWN] && fall.check(50))) {
                fall.reset();  
                y++;              
            }

            if(keyup || key.check(300)) {
                key.reset();
                if(in.key[SDLK_LEFT]) {
                    x--;
                }
                if(in.key[SDLK_RIGHT]) {
                    x++;
                }
            }

            keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT]);

            if(in.key[SDLK_UP]) {
                in.key[SDLK_UP] = false;
                form++;
                if(form >= cForms) {
                    form = 0;
                }
            }

            if(in.key[SDLK_SPACE]) {
                in.key[SDLK_SPACE] = false;
                
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
