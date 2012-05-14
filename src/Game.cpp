#include "../include/Game.h"
#include "../include/Exception.h"
#include "../include/SDL_Object.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Sound.h"
#include "../include/Music.h"
#include <vector>

using namespace std;

Game::Game(SDL & sdl) throw(Exception) : sdl(sdl),
xGrid(20), yGrid(150), wGrid(10), hGrid(20), squareSize(10),
wNext(4), hNext(2), xNext(50), yNext(130), initX(3), initY(0),
xStore(50), yStore(357),
fallSpeedInit(1000), fastFallSpeed(50), moveSpeed(100),
minFrameTime(30), changeSpeed(NULL),
empty(NULL), boomSnd(NULL), boom(NULL), disappearFrame(0), animSpeed(0),
music(NULL), digits(NULL), xCLines(180), yCLines(186), digitsSpace(0), cDigits(3) {

    this->empty = new RectSurface(this->sdl.getVideo(), this->squareSize, this->squareSize);
    this->empty->fill(0, 0, 0);
}

Game::~Game() {
    if(this->empty != NULL) {
        delete this->empty;
        this->empty = NULL;
    }

    if(this->boom != NULL) {
        delete this->boom;
        this->boom = NULL;
    }

    if(this->boomSnd != NULL) {
        delete this->boomSnd;
        this->boomSnd = NULL;
    }

    if(this->music != NULL) {
        delete this->music;
        this->music = NULL;
    }

    if(this->digits != NULL) {
        delete this->digits;
        this->digits = NULL;
    }

    const Shape * cur;
    while(!this->shapeArray.empty()) {
        cur = this->shapeArray.back();
        this->shapeArray.pop_back();
        if(cur != NULL) {
            delete cur;
        }
    }
}

void Game::setStoreCoords(unsigned int x, unsigned int y) {
    this->xStore = x;
    this->yStore = y;
}

void Game::setGridCoords(unsigned int x, unsigned int y) {
    this->xGrid = x;
    this->yGrid = y;
}

void Game::setGridSize(unsigned int w, unsigned int h) {
    this->wGrid = w;
    this->hGrid = h;
}

void Game::setNextCoords(unsigned int x, unsigned int y) {
    this->xNext = x;
    this->yNext = y;
}

void Game::setNextSize(unsigned int w, unsigned int h) {
    this->wNext = w;
    this->hNext = h;
}

void Game::setSquareSize(unsigned int s) {
    this->squareSize = s;
}

void Game::setInitCoords(unsigned int x, unsigned int y) {
    this->initX = x;
    this->initY = y;
}

void Game::setChangeSpeedFunction(changeSpeedFct changeSpeed) {
    this->changeSpeed = changeSpeed;
}

void Game::setSpeedInit(unsigned int speed) {
    this->fallSpeedInit = speed;
}

void Game::setFastSpeed(unsigned int speed) {
    this->fastFallSpeed = speed;
}

void Game::setMoveSpeed(unsigned int speed) {
    this->moveSpeed = speed;
}


void Game::setMaxFPS(unsigned int fps) {
    this->minFrameTime = 60/fps;
}

void Game::addShape(const Surface & surf, const shape & shapeShape,
                   unsigned int size, unsigned int count,
                   unsigned int initX, unsigned int initY) throw(Exception) {

    const Shape * shp = new Shape(surf, shapeShape, size, count, initX, initY);
    this->shapeArray.push_back(shp);
}

void Game::setEmpty(const string & image) throw(Exception) {
    if(this->empty != NULL) {
        delete this->empty;
    }
    this->empty = new ImageSurface(this->sdl.getVideo(), image.c_str());
}

void Game::setBoomAnimation(const string & image, unsigned int width,
                            unsigned int disappearFrame, unsigned int animSpeed) {

    if(this->boom != NULL) {
        delete this->boom;
    }
    this->boom = new AnimSurface(this->sdl.getVideo(), image.c_str(), width);
    this->disappearFrame = disappearFrame;
    this->animSpeed = animSpeed;
}

void Game::setBackground(const string & image) throw(Exception) {
    Video & video = this->sdl.getVideo();
    ImageSurface bg(video, image.c_str());
    video.blit(bg);
}

void Game::setBoomSound(const string & sound) throw(Exception) {
    if(this->boomSnd != NULL) {
        delete this->boomSnd;
    }
    this->boomSnd = new Sound(this->sdl.getAudio(), sound);
}

void Game::setMusic(const string & music) throw(Exception) {
    if(this->music != NULL) {
        delete this->music;
    }
    this->music = new Music(music);
    this->music->infinityPlay();
}

void Game::setDigits(const string & path, unsigned int width) throw(Exception) {
    if(this->digits != NULL) {
        delete this->digits;
    }
    this->digits = new AnimSurface(this->sdl.getVideo(), path.c_str(), width);
}

void Game::setCLinesPos(unsigned int x, unsigned int y) {
    this->xCLines = x;
    this->yCLines = y;
}

void Game::setCLinesDigits(unsigned int space, unsigned int count) {
    this->digitsSpace = space;
    this->cDigits = count;
}
