#include "../include/Jeu.h"
#include "../include/Exception.h"
#include "../include/SDL_Object.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Sound.h"
#include "../include/Music.h"
#include <vector>

using namespace std;

Jeu::Jeu(SDL & sdl) throw(Exception) : sdl(sdl),
xGrid(20), yGrid(150), wGrid(10), hGrid(20), squareSize(10),
wNext(4), hNext(2), xNext(50), yNext(130), initX(3), initY(0),
xStore(50), yStore(357),
fallSpeedInit(1000), fastFallSpeed(50), moveSpeed(100),
minFrameTime(30), changeSpeed(NULL),
empty(NULL), boomSnd(NULL), boom(NULL), disappearFrame(0), animSpeed(0),
music(NULL) {

    this->empty = new RectSurface(this->sdl.getVideo(), this->squareSize, this->squareSize);
    this->empty->fill(0, 0, 0);
}

Jeu::~Jeu() {
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

    const Shape * cur;
    while(!this->shapeArray.empty()) {
        cur = this->shapeArray.back();
        this->shapeArray.pop_back();
        if(cur != NULL) {
            delete cur;
        }
    }
}

void Jeu::setStoreCoords(unsigned int x, unsigned int y) {
    this->xStore = x;
    this->yStore = y;
}

void Jeu::setGridCoords(unsigned int x, unsigned int y) {
    this->xGrid = x;
    this->yGrid = y;
}

void Jeu::setGridSize(unsigned int w, unsigned int h) {
    this->wGrid = w;
    this->hGrid = h;
}

void Jeu::setNextCoords(unsigned int x, unsigned int y) {
    this->xNext = x;
    this->yNext = y;
}

void Jeu::setNextSize(unsigned int w, unsigned int h) {
    this->wNext = w;
    this->hNext = h;
}

void Jeu::setSquareSize(unsigned int s) {
    this->squareSize = s;
}

void Jeu::setInitCoords(unsigned int x, unsigned int y) {
    this->initX = x;
    this->initY = y;
}

void Jeu::setChangeSpeedFunction(changeSpeedFct changeSpeed) {
    this->changeSpeed = changeSpeed;
}

void Jeu::setSpeedInit(unsigned int speed) {
    this->fallSpeedInit = speed;
}

void Jeu::setFastSpeed(unsigned int speed) {
    this->fastFallSpeed = speed;
}

void Jeu::setMoveSpeed(unsigned int speed) {
    this->moveSpeed = speed;
}


void Jeu::setMaxFPS(unsigned int fps) {
    this->minFrameTime = 60/fps;
}

void Jeu::addShape(const Surface & surf, const shape & shapeShape,
                   unsigned int size, unsigned int count,
                   unsigned int initX, unsigned int initY) throw(Exception) {

    const Shape * shp = new Shape(surf, shapeShape, size, count, initX, initY);
    this->shapeArray.push_back(shp);
}

void Jeu::setEmpty(const string & image) throw(Exception) {
    if(this->empty != NULL) {
        delete this->empty;
    }
    this->empty = new ImageSurface(this->sdl.getVideo(), image.c_str());
}

void Jeu::setBoomAnimation(const string & image, unsigned int width,
                            unsigned int disappearFrame, unsigned int animSpeed) {

    if(this->boom != NULL) {
        delete this->boom;
    }
    this->boom = new AnimSurface(this->sdl.getVideo(), image.c_str(), width);
    this->disappearFrame = disappearFrame;
    this->animSpeed = animSpeed;
}

void Jeu::setBackground(const string & image) throw(Exception) {
    Video & video = this->sdl.getVideo();
    ImageSurface bg(video, image.c_str());
    video.blit(bg);
}

void Jeu::setBoomSound(const string & sound) throw(Exception) {
    if(this->boomSnd != NULL) {
        delete this->boomSnd;
    }
    this->boomSnd = new Sound(this->sdl.getAudio(), sound);
}

void Jeu::setMusic(const string & music) throw(Exception) {
    if(this->music != NULL) {
        delete this->music;
    }
    this->music = new Music(music);
    this->music->infinityPlay();
}

