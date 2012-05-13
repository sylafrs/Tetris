#include "../include/Jeu.h"
#include "../include/Exception.h"
#include "../include/SDL_Object.h"
#include "../include/Input.h"
#include "../include/Video.h"
#include "../include/Random.h"
#include "../include/Structure.h"
#include "../include/Unit.h"
#include "../include/Surface.h"
#include "../include/Chrono.h"

using namespace std;

void Jeu::play() throw(Exception) {

    Input & in = this->sdl.getInput();
    Video & video = this->sdl.getVideo();

    RectSurface nextZone(video, this->squareSize*this->wNext,
                                this->squareSize*this->hNext);

    RectSurface gameZone(video, this->squareSize*this->wGrid,
                                this->squareSize*this->hGrid);
                                
    RectSurface storeZone(video, this->squareSize*this->wNext,
                                 this->squareSize*this->hNext);

    Random rand;
    rand.setMin(0);
    rand.setMax(this->shapeArray.size()-1);

    Structure structure(this->wGrid, this->hGrid);
    Unit unit(structure, this->initX, this->initY, *this->shapeArray.at(rand.next()));
    const Shape * next = (this->shapeArray.at(rand.next()));
    const Shape * stored = NULL;
    bool store = false;

    unsigned int fallSpeed = this->fallSpeedInit;

    bool keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT] && !in.key[SDLK_a] && !in.key[SDLK_d]);
    Chrono fall, key;

    RectSurface gameZoneBG(video,   this->squareSize*this->wGrid,
                                    this->squareSize*this->hGrid);

    for(unsigned int x = 0; x < wGrid; x++) {
        for(unsigned int y = 0; y < hGrid; y++) {
            gameZoneBG.blit(*this->empty, x*this->squareSize, y*this->squareSize);
        }
    }

    nextZone.blit(gameZoneBG, 0, 0, 0, 0, this->wNext*this->squareSize,
                                          this->hNext*this->squareSize);
    storeZone.blit(gameZoneBG, 0, 0, 0, 0, this->wNext*this->squareSize,
                                           this->hNext*this->squareSize);                                      
    gameZone.blit(gameZoneBG);

    blit(gameZone, unit);
    blit(nextZone, *next, -next->getInitX()/2, -next->getInitY(), 0);
    blit(gameZone, structure);

    video.blit(gameZone, this->xGrid, this->yGrid);
    video.blit(nextZone, this->xNext, this->yNext);
    video.blit(storeZone, this->xStore, this->yStore);

    sdl.update();
    bool lose = false;

    Chrono delay;
    while(!in.quit && !in.key[SDLK_ESCAPE] && !lose) {

        if(fall.check(fallSpeed)) {
            if(!unit.bottom()) {

                if(this->changeSpeed != NULL)
                    this->changeSpeed(fallSpeed);

                store = false;
                structure.add(unit);

                unit.change(*next);
                next = (this->shapeArray.at(rand.next()));

                nextZone.blit(gameZoneBG, 0, 0, 0, 0, this->wNext*this->squareSize,
                                                      this->hNext*this->squareSize);
                blit(nextZone, *next, -next->getInitX(), -next->getInitY(), 0);
                video.blit(nextZone, xNext, yNext);

                if(structure.check(unit)) {
                    lose = true;
                }
            }
            fall.reset();
        }

        if(in.key[SDLK_LSHIFT] && !store) {
            store = true;
            if(stored != NULL) {
                const Shape * tmp = stored;
                stored = &(unit.getShape());
                unit.change(*tmp);
            }
            else {
                stored = &(unit.getShape());
                unit.change(*next);
                next = (this->shapeArray.at(rand.next()));

                nextZone.blit(gameZoneBG, 0, 0, 0, 0, this->wNext*this->squareSize,
                                                      this->hNext*this->squareSize);
                blit(nextZone, *next, -next->getInitX(), -next->getInitY(), 0);
                video.blit(nextZone, xNext, yNext);
            }
            
            storeZone.blit(gameZoneBG, 0, 0, 0, 0, this->wNext*this->squareSize,
                                                   this->hNext*this->squareSize);
                                                      
            blit(storeZone, *stored, -stored->getInitX(), -stored->getInitY(), 0);
            video.blit(storeZone, xStore, yStore);

            if(structure.check(unit)) {
                lose = true;
            }
        }

        if((in.key[SDLK_DOWN] || in.key[SDLK_s]) && fall.check(fastFallSpeed)) {
            unit.bottom();
        }

        if(keyup || key.check(moveSpeed)) {
            key.reset();
            if(in.key[SDLK_LEFT] || in.key[SDLK_q]) {
                unit.left();
            }
            if(in.key[SDLK_RIGHT] || in.key[SDLK_d]) {
                unit.right();
            }
        }

        keyup = (!in.key[SDLK_LEFT] && !in.key[SDLK_RIGHT] && !in.key[SDLK_a] && !in.key[SDLK_d]);

        if(in.key[SDLK_UP] || in.key[SDLK_z]) {
            in.key[SDLK_UP] = in.key[SDLK_z] = false;
            unit.rotate();
        }

        if(in.key[SDLK_SPACE]) {
            in.key[SDLK_SPACE] = false;
            unit.fall();

            if(this->changeSpeed != NULL)
                this->changeSpeed(fallSpeed);

            store = false;
            structure.add(unit);

            unit.change(*next);
            next = (this->shapeArray.at(rand.next()));

            nextZone.blit(gameZoneBG, 0, 0, 0, 0, this->wNext*this->squareSize,
                                                  this->hNext*this->squareSize);
            blit(nextZone, *next, -next->getInitX(), -next->getInitY(), 0);
            video.blit(nextZone, xNext, yNext);

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

        if(structure.checkLines() && this->boom != NULL) {
            delay.reset();

            RectSurface square(video, this->squareSize, this->squareSize);
            for(unsigned int step = 0; step < this->boom->getCFrames(); step++) {

                square.fill(255,255,255);
                blit(square, *this->boom, step);
                square.setKey(255, 255, 255);
                for(unsigned int i = 0; i < structure.getLineCount(); i++) {
                    if(structure.checkLine(i)) {
                        if(step < this->disappearFrame) {
                            blitLine(i, gameZone, structure);
                        }
                        else {
                            blitLineOf(i, gameZone, *empty, structure);
                        }
                        blitLineOf(i, gameZone, square, structure);
                    }
                }

                video.blit(gameZone, this->xGrid, this->yGrid);
                delay.wait(this->animSpeed);
                sdl.update();
            }
            structure.eraseFullLines();
        }
    }

}
