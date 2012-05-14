#include "../include/Unit.h"
#include "../include/Shape.h"
#include "../include/Structure.h"

Unit::Unit(const Structure & structure, unsigned int initX, unsigned int initY, const Shape & shape) :
structure(structure), initX(initX), initY(initY) {
    change(shape);
}

void Unit::change(const Shape & shape) {
    this->x = this->initX - shape.getInitX();
    this->y = this->initY - shape.getInitY();
    this->form = 0;
    this->shape = &shape;
}

bool Unit::left() {
    if(!this->structure.allowLeft(*this)) {
        return false;
    }

    this->x = this->x - 1;
    this->checkSides();
    return true;
}

bool Unit::right() {
    if(!this->structure.allowRight(*this)) {
        return false;
    }

    this->x = this->x + 1;
    this->checkSides();
    return true;
}

void Unit::fall() {
    while(this->bottom());
}

bool Unit::bottom() {
    bool ok = (!this->structure.check(*this));
    if(ok) {
        this->y = this->y + 1;
    }
    return ok;
}

bool Unit::rotate() {
    this->form = this->form + 1;
    if(this->form >= shape->getCForms()) {
        this->form = 0;
    }
    this->checkSides();
    return true;
}

bool Unit::rotateInv() {
    this->form = this->form - 1;
    if(this->form < 0) {
        this->form = shape->getCForms() - 1;
    }
    this->checkSides();
    return true;
}

void Unit::checkSides() {
    this->shape->checkSides(this->x, this->y, structure.getWGrid(), structure.getHGrid(), this->form);
}

const Shape & Unit::getShape() const {
    return *(this->shape);
}

int Unit::getX() const {
    return this->x;
}

int Unit::getY() const {
    return this->y;
}

int Unit::getForm() const {
    return this->form;
}

bool blit(Surface & surface, const Unit & unit) {
    return blit(surface, unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

