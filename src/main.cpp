#include "../include/SDL_Object.h"
#include "../include/constantes.h"
#include "../include/shapes.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Shape.h"
#include "../include/Structure.h"
#include "../include/Unit.h"
#include "../include/Random.h"
#include "../include/Chrono.h"

#include <iostream>

using namespace std;

void speedUp(int & current) {

}

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

        RectSurface prevZone(video, squareSize*initShapeWidth, squareSize*initShapeHeight);
        RectSurface gameZone(video, squareSize*wGrid, squareSize*hGrid);
        ImageSurface rouge (video, "imgs/rouge.bmp");
        ImageSurface bleu  (video, "imgs/bleu.bmp");
        ImageSurface vert  (video, "imgs/vert.bmp");
        ImageSurface jaune (video, "imgs/jaune.bmp");
        ImageSurface orange(video, "imgs/orange.bmp");
        ImageSurface cyan  (video, "imgs/cyan.bmp");
        ImageSurface violet(video, "imgs/violet.bmp");
        ImageSurface vide  (video, "imgs/vide.bmp");

        unsigned int disappearStep = 3;
        AnimSurface boom(video, "imgs/boom.bmp", squareSize);
        
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

        Random rand;
        rand.setMin(0);
        rand.setMax(arraySize-1);
        
        Structure structure;
        Unit unit(structure, array[rand.next()]);
        Shape * prev = &array[rand.next()];

        int fallSpeed = fallSpeedInit;

        bool keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT] && !in.key[SDLK_a] && !in.key[SDLK_d]);
        Chrono fall, key;

        RectSurface gameZoneBG(video, squareSize*wGrid, squareSize*hGrid);
        for(unsigned int x = 0; x < wGrid; x++) {
            for(unsigned int y = 0; y < hGrid; y++) {
                gameZoneBG.blit(vide, x*squareSize, y*squareSize);    
            }
        }
        
        prevZone.blit(gameZoneBG, 0, 0, 0, 0, initShapeWidth*squareSize, initShapeHeight*squareSize);
        gameZone.blit(gameZoneBG);
        blit(gameZone, unit);
        blit(prevZone, *prev, -prev->getInitX()/2, -prev->getInitY(), 0);
        blit(gameZone, structure);
        video.blit(gameZone, xGrid, yGrid);
        video.blit(prevZone, xPrev, yPrev);

        sdl.update();
        bool lose = false;

        Chrono delay;
        while(!in.quit && !in.key[SDLK_ESCAPE] && !lose) {

            if(fall.check(fallSpeed)) {
                if(!unit.bottom()) {
                    speedUp(fallSpeed);
                    structure.add(unit);
                                                            
                    unit.change(*prev);
                    prev = &array[rand.next()];
                    
                    prevZone.blit(gameZoneBG, 0, 0, 0, 0, initShapeWidth*squareSize, initShapeHeight*squareSize);
                    blit(prevZone, *prev, -prev->getInitX(), -prev->getInitY(), 0); 
                    video.blit(prevZone, xPrev, yPrev);
                    
                    if(structure.check(unit)) {
                        lose = true;
                    }
                }
                fall.reset();
            }

            if((in.key[SDLK_DOWN] || in.key[SDLK_s]) && fall.check(fastFallSpeed)) {
                unit.bottom();
            }

            if(keyup || key.check(moveSpeed)) {
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
                unit.fall();
                   
                speedUp(fallSpeed);
                structure.add(unit);
                                                        
                unit.change(*prev);
                prev = &array[rand.next()];
                
                prevZone.blit(gameZoneBG, 0, 0, 0, 0, initShapeWidth*squareSize, initShapeHeight*squareSize);
                blit(prevZone, *prev, -prev->getInitX(), -prev->getInitY(), 0); 
                video.blit(prevZone, xPrev, yPrev);
                
                if(structure.check(unit)) {
                    lose = true;
                }
            }

            
            gameZone.blit(gameZoneBG);
            blit(gameZone, unit);
            blit(gameZone, structure);
            video.blit(gameZone, xGrid, yGrid);
            
            delay.wait(minFrameTime);
            sdl.update();
            
            if(structure.checkLines()) {
                delay.reset();
                
                RectSurface square(video, squareSize, squareSize);
                for(unsigned int step = 0; step < boom.getCFrames(); step++) {
                    
                    square.fill(255,255,255);
                    blit(square, boom, step);
                    square.setKey(255, 255, 255);
                    for(unsigned int i = 0; i < structure.getLineCount(); i++) {
                        if(structure.checkLine(i)) {
                            if(step < disappearStep) {
                                blitLine(i, gameZone, structure);
                            }
                            else {
                                blitLineOf(i, gameZone, vide);
                            }
                            blitLineOf(i, gameZone, square);
                        }
                    } 
                    
                    video.blit(gameZone, xGrid, yGrid);
                    delay.wait(100);
                    sdl.update();
                }
                structure.eraseFullLines();                    
            }
        }
    }
    catch(const Exception & e) {
        cerr << e << endl;
    }

    return 0;
}
