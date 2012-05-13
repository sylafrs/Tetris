#include "../include/Jeu.h"
#include "../include/SDL_Object.h"
#include "../include/Surface.h"
#include "../include/Video.h"
#include "../include/Shape.h"

#include <vector>
#include <iostream>

using namespace std;

void defaultSpeedUp(unsigned int & current) {

}

Jeu::Jeu(SDL & sdl) throw(Exception) : sdl(sdl), changeSpeed(defaultSpeedUp), empty(NULL),
xGrid(20), yGrid(150), wGrid(10), hGrid(20), squareSize(10),
wNext(4), hNext(2), xNext(50), yNext(130), initX(3), initY(0),
fallSpeedInit(1000), fastFallSpeed(50), moveSpeed(100),
minFrameTime(30) {

    empty = new RectSurface(this->sdl.getVideo(), this->squareSize, this->squareSize);
    empty->fill(0, 0, 0);
}

Jeu::~Jeu() {
    if(empty != NULL) {
        delete empty;
        empty = NULL;
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

}

void Jeu::setSquareSize(unsigned int s) {

}

void Jeu::setInitCoords(unsigned int x, unsigned int y) {

}

void Jeu::setChangeSpeedFunction(changeSpeedFct changeSpeed) {

}

void Jeu::setSpeedInit(unsigned int speed) {

}

void Jeu::setFastSpeed(unsigned int speed) {

}

void Jeu::setMoveSpeed(unsigned int speed) {

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

void Jeu::setEmpty(std::string image) throw(Exception) {
    this->empty = new ImageSurface(this->sdl.getVideo(), image.c_str());
}

void Jeu::setBackground(std::string image) throw(Exception) {
    Video & video = this->sdl.getVideo();
    ImageSurface bg(video, image.c_str());
    video.blit(bg);
}

