#ifndef STRUCTURE_H_
#define STRUCTURE_H_

    #include "Surface.h"
    #include <list>
    #include <vector>

    class Unit;
    class Shape;

    class Structure {

        private:
            std::list<std::vector<const Surface *> > structure;

        public:
            bool check(const Unit & unit) const ;
            void add(const Unit & unit);
            bool check(const Shape & shape, int x, int y, int form) const ;
            void add(const Shape & shape, int x, int y, int form);

    };

    #include "Unit.h"
    #include "Shape.h"

#endif//STRUCTURE_H_
