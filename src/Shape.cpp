#include "../include/constantes.h"
#include "../include/Surface.h"
#include "../include/Shape.h"

Shape::Shape(const Surface & surface,
             const shape & shapeArray,
             unsigned int size, unsigned int cForms,
             unsigned int initX, unsigned int initY) :
surface(surface), shapeArray(shapeArray),
size(size), cForms(cForms),
initX(initX), initY(initY)
{

}

Shape::~Shape() {

}

const Surface & Shape::getSurface() const {
    return this->surface;
}

unsigned int Shape::getSize() const {
    return this->size;
}

unsigned int Shape::getCForms() const {
    return this->cForms;
}

unsigned int Shape::getInitX() const {
    return this->initX;
}

unsigned int Shape::getInitY() const {
    return this->initY;
}

bool Shape::check(unsigned int x, unsigned int y, unsigned int num) const {
    return this->shapeArray[num][y][x];
}

bool Shape::checkX(int & x, int max, unsigned int num) const {
    int i, j;
    int first, last; // column

    for(i = 0; i < this->size; i++) {
        for(j = 0; j < this->size; j++) {
            if(this->shapeArray[num][j][i]) {
                if(i < first)   first = i;
                if(i > last)    last = i;
            }
        }
    }

    if(x < -first) {
        x = -first;
    }

    if(x + last >= max) {
        x = max-last-1;
    }

    return true;
}

bool blitInit(Surface & surface, const Shape & shape,
              unsigned int x, unsigned int y) {

    return true;
}


bool blit(Surface & surface, const Shape & shape,
          unsigned int x, unsigned int y, unsigned int num) {

    unsigned int s = shape.getSize();
    const Surface & surfShape = shape.getSurface();

    unsigned int i, j;
    for(i = 0; i < s; i++) {
        for(j = 0; j < s; j++) {
            if(shape.check(i, j, num)) {
                surface.blit(surfShape, (i+x)*surfShape.getWidth(), (y+j)*surfShape.getHeight());
            }
        }
    }

    return true;
}

