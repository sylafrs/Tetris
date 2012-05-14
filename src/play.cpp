#include "../include/Game.h"
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

void Game::play() throw(Exception) {

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

    if(this->digits != NULL) {
        for(unsigned int i = 0; i < this->cDigits; i++) {
            blit(video, *this->digits, 0,
                        this->xCLines + (this->digits->getFrameWidth() + this->digitsSpace)*i,
                        this->yCLines);
        }
    }

    sdl.update();
    bool lose = false;

    Chrono delay;
    unsigned int cLines = 0;
    while(!in.quit && !in.key[SDLK_ESCAPE] && !lose) {

        if(in.key[SDLK_m] && this->music != NULL) {
            in.key[SDLK_m] = false;
            if(this->music->paused()) {
                this->music->resume();
            }
            else {
                this->music->pause();
            }
        }

        if(fall.check(fallSpeed)) {
            if(!unit.bottom()) {
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

        unsigned int lines = structure.checkLines();
        if(lines > 0 && this->boom != NULL) {
            cLines+=lines;

            if(this->digits != NULL) {
                unsigned int div = 1;
                unsigned int i, d;
                unsigned int tmpCLines = cLines;
                for(i = 0; i < this->cDigits - 1; i++) {
                    div *= 10;
                }
                for(i = 0; i < this->cDigits; i++) {
                    d = tmpCLines/div;
                    tmpCLines -= (d*div);
                    div /= 10;

                    blit(video, *this->digits, d,
                         this->xCLines+(this->digits->getFrameWidth()+this->digitsSpace)*i,
                         this->yCLines);
                }
            }

            if(this->changeSpeed != NULL) {
                while(lines > 0) {
                    this->changeSpeed(fallSpeed);
                    lines--;
                }
            }

            if(this->boom != NULL) {
                delay.reset();
                if(this->boomSnd != NULL) {
                    this->boomSnd->play();
                }

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

    if(this->boom != NULL && !in.quit && !in.key[SDLK_ESCAPE]) {
        for(unsigned int repeat = 0; repeat < 3; repeat++) {
            if(this->boomSnd != NULL) {
                this->boomSnd->play();
            }

            RectSurface square(video, this->squareSize, this->squareSize);
            for(unsigned int step = 0; step < this->boom->getCFrames(); step++) {

                square.fill(255,255,255);
                blit(square, *this->boom, step);
                square.setKey(255, 255, 255);
                for(unsigned int i = 0; i < this->hGrid; i++) {
                    if(step < this->disappearFrame) {
                        structure.clear();
                    }
                    else {
                        blitLineOf(i, gameZone, *empty, structure);
                    }
                    blitLineOf(i, gameZone, square, structure);
                }

                video.blit(gameZone, this->xGrid, this->yGrid);
                delay.wait(this->animSpeed);
                sdl.update();
            }
        }
    }
}

