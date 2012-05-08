#include "../include/Unit.h"
#include "../include/constantes.h"

Unit::Unit(const Shape & shape) {
    change(shape);
}

void Unit::change(const Shape & shape) {
    this->x = initX - shape.getInitX();
    this->y = initY - shape.getInitY();
    this->form = 0;
    this->shape = &shape;
}

void Unit::left() {
    this->x = this->x - 1;
    this->checkX();
}

void Unit::right() {
    this->x = this->x + 1;
    this->checkX();
}

void Unit::fall() {

}

void Unit::bottom() {
    this->y = this->y + 1;
    this->checkX();
}

void Unit::rotate() {
    this->form = this->form + 1;
    if(this->form >= shape->getCForms()) {
        this->form = 0;
    }

    this->checkX();
}

bool Unit::checkX() {
    return this->shape->checkX(this->x, wGrid, this->form);
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

bool blitInit(Surface & surface, const Unit & unit) {
    return blitInit(surface, unit.getShape(), unit.getX(), unit.getY());
}

bool blit(Surface & surface, const Unit & unit) {
    return blit(surface, unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

