#include "../include/Structure.h"
#include "../include/Unit.h"

bool Structure::check(const Unit & unit) const {
    return this->check(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

void Structure::add(const Unit & unit) {
    this->add(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

bool Structure::check(const Shape & shape, int x, int y, int form) const {

    if(y + shape.getMaxLine(form)+1 >= hGrid && this->structure.empty()) {
        return true;
    }

    // On récupère les différentes lignes


    return false;
}

void Structure::add(const Shape & shape, int x, int y, int form) {



}

