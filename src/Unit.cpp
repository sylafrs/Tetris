#include "../include/Unit.h"
#include "../include/Shape.h"
#include "../include/Structure.h"
#include "../include/constantes.h"

Unit::Unit(const Structure & structure, const Shape & shape) : structure(structure) {
    change(shape);
}

void Unit::change(const Shape & shape) {
    this->x = initX - shape.getInitX();
    this->y = initY - shape.getInitY();
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

void Unit::checkSides() {
    this->shape->checkSides(this->x, this->y, wGrid, hGrid, this->form);
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

