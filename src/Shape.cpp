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

    unsigned int i, j, n;
    for(n = 0; n < this->cForms; n++) {

        this->maxMinArray[n][MIN_COL] = this->maxMinArray[n][MIN_LIN] = this->size;
        this->maxMinArray[n][MAX_COL] = this->maxMinArray[n][MAX_LIN] = 0;

        for(i = 0; i < this->size; i++) {
            for(j = 0; j < this->size; j++) {
                if(this->shapeArray[n][j][i]) {
                    if((int)i < this->maxMinArray[n][MIN_COL])
                        this->maxMinArray[n][MIN_COL] = (int)i;
                    if((int)i > this->maxMinArray[n][MAX_COL])
                        this->maxMinArray[n][MAX_COL] = (int)i;
                    if((int)j < this->maxMinArray[n][MIN_LIN])
                        this->maxMinArray[n][MIN_LIN] = (int)j;
                    if((int)j > this->maxMinArray[n][MAX_LIN])
                        this->maxMinArray[n][MAX_LIN] = (int)j;
                }
            }
        }
    }

}

Shape::~Shape() {

}

int Shape::getMaxLine(unsigned int form) const {
    return this->maxMinArray[form][MAX_LIN];
}

int Shape::getMinLine(unsigned int form) const{
    return this->maxMinArray[form][MIN_LIN];
}

int Shape::getMaxColumn(unsigned int form) const{
    return this->maxMinArray[form][MAX_COL];
}

int Shape::getMinColumn(unsigned int form) const{
    return this->maxMinArray[form][MIN_COL];
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

bool Shape::get(unsigned int x, unsigned int y, unsigned int num) const {
    return this->shapeArray[num][y][x];
}

unsigned int Shape::getMaxInColumn(unsigned int c, unsigned int form) const {

    unsigned int l = 0;
    unsigned int i;

    unsigned int minLine = this->getMinLine(form);
    unsigned int maxLine = this->getMaxLine(form);
    for(i = minLine; i <= maxLine; i++) {
        if(this->get(c, i, form)) {
            l = i;
        }
    }

    return l;
}

unsigned int Shape::getMaxInLine(unsigned int l, unsigned int form) const {
    unsigned int c;
    unsigned int i;

    unsigned int minColumn = this->getMinColumn(form);
    unsigned int maxColumn = this->getMaxColumn(form);
    for(i = minColumn; i <= maxColumn; i++) {
        if(this->get(i, l, form)) {
            c = i;
        }
    }

    return c;
}

unsigned int Shape::getMinInLine(unsigned int l, unsigned int form) const {
    unsigned int c;
    unsigned int i;

    unsigned int minColumn = this->getMinColumn(form);
    unsigned int maxColumn = this->getMaxColumn(form);
    for(i = maxColumn; i >= minColumn; i--) {
        if(this->get(i, l, form)) {
            c = i;
        }
    }

    return c;
}

void Shape::checkSides(int & x, int & y, int maxX, int maxY, unsigned int num) const {

    int firstX = this->getMinColumn(num);
    int lastX = this->getMaxColumn(num);
    int firstY = this->getMinLine(num);
    int lastY = this->getMaxLine(num);

    if(x < -firstX) {
        x = -firstX;
    }

    if(x + lastX >= maxX) {
        x = maxX-lastX-1;
    }

    if(y < -firstY) {
        y = -firstY;
    }

    if(y + lastY >= maxY) {
        y = maxY-lastY-1;
    }
}

bool blit(Surface & surface, const Shape & shape,
          unsigned int x, unsigned int y, unsigned int num) {

    unsigned int s = shape.getSize();
    const Surface & surfShape = shape.getSurface();

    unsigned int i, j;
    for(i = 0; i < s; i++) {
        for(j = 0; j < s; j++) {
            if(shape.get(i, j, num) && (int)(i+(int)x) >= 0 && (int)((int)y+j) >= 0) {
                surface.blit(surfShape, (i+x)*surfShape.getWidth(), (y+j)*surfShape.getHeight());
            }
        }
    }

    return true;
}

