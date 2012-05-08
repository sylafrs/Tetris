#include "../include/Structure.h"
#include "../include/Unit.h"

bool Structure::check(const Unit & unit) {
    return this->check(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

bool Structure::add(const Unit & unit) {
    return this->add(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

bool Structure::check(const Shape & shape, int x, int y, int form) {
    #warning TODO here

    return true;
}

bool Structure::add(const Shape & shape, int x, int y, int form) {

    if(!this->check(shape, x, y, form)) {
        return false;
    }


    return false;
}
