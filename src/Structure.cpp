#include "../include/Structure.h"
#include "../include/Unit.h"

#include <iostream>

using namespace std;

bool Structure::check(const Unit & unit) const {
    return this->check(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

void Structure::add(const Unit & unit) {
    this->add(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

line & Structure::getLine(unsigned int n) {
    list<line>::iterator it = this->structure.begin();
    for(unsigned int i = 0; i < n; i++) it++;
    return *it;
}

const line & Structure::getLine(unsigned int n) const {
    list<line>::const_iterator it = this->structure.begin();
    for(unsigned int i = 0; i < n; i++) it++;
    return *it;
}

bool Structure::check(const Shape & shape, int x, int y, int form) const {

    if(y + shape.getMaxLine(form)+1 >= hGrid && this->structure.empty()) {
        return true;
    }

    bool touch = false;
    unsigned int i = shape.getMinColumn(form);
    unsigned int maxI = shape.getMaxColumn(form);
    unsigned int cLines = this->getLineCount();
    while(!touch && i <= maxI) {

        unsigned int test = shape.getMaxInColumn(i, form) + y + 2;
        unsigned int lineNum = hGrid-test;
        cout << "test : " << lineNum << endl;
        if(lineNum < cLines) {
            const line l = this->getLine(lineNum);
            touch = (l.at(x+i) != NULL);
        }

        i++;
    }
    cout << "-------------------" << endl;
    return touch;
}

void Structure::add(const Shape & shape, int x, int y, int form) {

    const Surface & surface = shape.getSurface();

    unsigned int i = shape.getMaxLine(form);
    unsigned int minI = shape.getMinLine(form);
    unsigned int cLines = this->getLineCount();
    while(i >= minI) {
        unsigned int coord = shape.getMaxInColumn(i, form) + y + 1;
        unsigned int lineNum = hGrid-coord;
        while(lineNum+1 >= cLines) {
            cout << "Ajout : " << lineNum << endl;
            this->structure.push_front(line(wGrid, (const Surface *)NULL));
            cLines++;
        }
        cout << "-------------------" << endl;
        #error HERE

        unsigned int j = shape.getMinColumn(form);
        unsigned int maxJ = shape.getMaxColumn(form);
        line iLine = this->getLine(lineNum);
        while(j <= maxJ) {
            iLine[j+x] = (shape.get(j, i, form) ? &surface : NULL);
            j++;
        }

        i--;
    }

}

unsigned int Structure::getLineCount() const {
    return structure.size();
}

const Surface * Structure::get(unsigned int x, unsigned int y) const {
    y = hGrid - y;
    if(y > this->structure.size()) {
        return NULL;
    }

    return this->getLine(y).at(x);
}

void blit(Surface & surface, const Structure & structure) {
    unsigned int len = structure.getLineCount();

    for(unsigned int i = 0; i < len; i++) {
        for(unsigned int j = 0; j < (unsigned int)wGrid; j++) {
            const Surface * square = structure.get(j, i);
            if(square != NULL) {
                surface.blit(*square, i*square->getWidth(), j*square->getHeight());
            }
        }
    }
}

