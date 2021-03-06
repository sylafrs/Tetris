#include "../include/Structure.h"
#include "../include/Unit.h"

using namespace std;

Structure::Structure(unsigned int wGrid, unsigned int hGrid) :
wGrid(wGrid), hGrid(hGrid) {

}

Structure::~Structure() {
    this->structure.clear();
}

unsigned int Structure::getHGrid() const {
    return this->hGrid;
}

unsigned int Structure::getWGrid() const {
    return this->wGrid;
}

bool Structure::check(const Unit & unit) const {
    return this->check(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

void Structure::add(const Unit & unit) {
    this->add(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

bool Structure::allowLeft(const Unit & unit) const {
    return this->allowLeft(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

bool Structure::allowRight(const Unit & unit) const {
    return this->allowRight(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

bool Structure::allowRotL(const Unit & unit) const {
    return this->allowRotL(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
}

bool Structure::allowRotR(const Unit & unit) const {
    return this->allowRotR(unit.getShape(), unit.getX(), unit.getY(), unit.getForm());
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

    if(y + shape.getMaxLine(form)+1 >= (int)this->hGrid) {
        return true;
    }

    bool touch = false;
    unsigned int i = shape.getMinColumn(form);
    unsigned int maxI = shape.getMaxColumn(form);
    unsigned int cLines = this->getLineCount();
    while(!touch && i <= maxI) {

        unsigned int test = shape.getMaxInColumn(i, form) + y + 2;
        unsigned int lineNum = this->hGrid-test;
        if(lineNum < cLines) {
            const line l = this->getLine(lineNum);
            touch = (l.at(x+i) != NULL);
        }

        i++;
    }
    return touch;
}

void Structure::add(const Shape & shape, int x, int y, int form) {

    const Surface & surface = shape.getSurface();

    unsigned int max = y + shape.getMinLine(form);
    unsigned int numLine = this->hGrid - max;
    unsigned int cLines = this->getLineCount();
    while(cLines < numLine) {
        this->structure.push_back(line(this->wGrid, (const Surface *)NULL));
        cLines++;
    }

    unsigned int i = shape.getMinLine(form);
    unsigned int iMax = shape.getMaxLine(form);
    unsigned int j;
    unsigned int size = shape.getSize();
    while(i <= iMax) {
        numLine = this->hGrid - (y + i + 1);
        line & l = this->getLine(numLine);
        j = 0;
        while(j < size) {
            if(shape.get(j, i, form)) {
                l[j+x] = &surface;
            }
            j++;
        }
        i++;
    }
}

unsigned int Structure::getLineCount() const {
    return this->structure.size();
}

const Surface * Structure::get(unsigned int x, unsigned int y) const {
    if(y >= this->structure.size()) {
        return NULL;
    }

    return this->getLine(y).at(x);
}

bool Structure::allowLeft(const Shape & shape, int x, int y, int form) const {

    unsigned int i = shape.getMinLine(form);
    unsigned int max = shape.getMaxLine(form);
    unsigned int c;

    while(i <= max) {
        c = shape.getMinInLine(i, form);
        if(x + (int)c > 0) {
            if(this->get((int)c + x - 1, this->hGrid - (y + i + 1)) != NULL) {
                return false;
            }
        }

        i++;
    }

    return true;
}

bool Structure::allowRight(const Shape & shape, int x, int y, int form) const {
    unsigned int i = shape.getMinLine(form);
    unsigned int max = shape.getMaxLine(form);
    unsigned int c;

    while(i <= max) {
        c = shape.getMaxInLine(i, form);
        if(x + (int)c < (int)this->wGrid-1) {
            if(this->get((int)c + x + 1, this->hGrid - (y + i + 1)) != NULL) {
                return false;
            }
        }

        i++;
    }

    return true;
}

#warning (function incomplete)
bool Structure::allowRotL(const Shape & shape, int x, int y, unsigned int form) const {
    form--;
    if((int)form < 0) {
        form = shape.getCForms();
    }

    shape.checkSides(x, y, this->wGrid, this->hGrid, form);

    unsigned int i = shape.getMinLine(form);
    unsigned int iMax = shape.getMaxLine(form);
    unsigned int j, l;
    unsigned int jMax = shape.getSize();
    bool ok = true;
    while(i <= iMax && ok) {

        l = this->hGrid - (y + i + 1);
        for(j = 0; j < jMax && ok; j++) {
            ok = (shape.get(j, i, form) != 1 || this->get(x+j, l) == NULL);
        }
        i++;
    }

    return ok;
}

#warning (function incomplete)
bool Structure::allowRotR(const Shape & shape, int x, int y, unsigned int form) const {
    form++;
    if((int)form >= shape.getCForms()) {
        form = 0;
    }

    shape.checkSides(x, y, this->wGrid, this->hGrid, form);

    unsigned int i = shape.getMinLine(form);
    unsigned int iMax = shape.getMaxLine(form);
    unsigned int j, l;
    unsigned int jMax = shape.getSize();
    bool ok = true;
    while(i <= iMax && ok) {

        l = this->hGrid - (y + i + 1);
        for(j = 0; j < jMax && ok; j++) {
            ok = (shape.get(j, i, form) != 1 || this->get(x+j, l) == NULL);
        }
        i++;
    }

    return ok;
}

bool Structure::checkLine(unsigned int l) const {
    const line & curLine = this->getLine(l);

    bool full = true;
    line::const_iterator lineIt = curLine.begin();
    while(full && lineIt != curLine.end()) {
        full = (*lineIt != NULL);
        lineIt++;
    }

    return full;
}

unsigned int Structure::checkLines() const {
    list<line>::const_iterator it = this->structure.begin();
    unsigned int cLines = 0;
    bool full;
    line::const_iterator lineIt;

    while(it != this->structure.end()) {
        const line & curLine = *it;

        full = true;
        lineIt = curLine.begin();
        while(full && lineIt != curLine.end()) {
            full = (*lineIt != NULL);
            lineIt++;
        }

        if(full) {
            cLines++;
        }
        it++;
    }

    return cLines;
}

void Structure::eraseFullLines() {

    list<line>::iterator it = this->structure.begin();
    bool full;
    line::iterator lineIt;

    while(it != this->structure.end()) {
        line & curLine = *it;

        full = true;
        lineIt  = curLine.begin();
        while(full && lineIt != curLine.end()) {
            full = (*lineIt != NULL);
            lineIt++;
        }

        if(full) {
            it = this->structure.erase(it);
        }
        else {
            it++;
        }
    }
}

void Structure::clear() {
    this->structure.clear();
}

void blit(Surface & surface, const Structure & structure) {
    unsigned int len = structure.getLineCount();

    for(unsigned int i = 0; i < len; i++) {
        blitLine(i, surface, structure);
    }
}

void blitLine(unsigned int l, Surface & surface, const Structure & structure) {
    for(unsigned int i = 0; i < structure.getWGrid(); i++) {
        const Surface * square = structure.get(i, l);
        if(square != NULL) {
            surface.blit(*square, i*square->getWidth(),
                        ((int)structure.getHGrid()-(int)(l+1))*square->getHeight());
        }
    }
}

void blitLineOf(unsigned int l, Surface & surface, const Surface & square, const Structure & structure) {
    for(unsigned int i = 0; i < structure.getWGrid(); i++) {
        surface.blit(square, i*square.getWidth(),
                    ((int)structure.getHGrid()-(int)(l+1))*square.getHeight());
    }
}
