#ifndef STRUCTURE_H_
#define STRUCTURE_H_

    #include "Shape.h"
    #include "Surface.h"
    #include <list>
    #include <vector>

    class Structure {

        private:
            std::list<std::vector<const Surface *> > structure;

        public:
            bool check(const Shape & shape, int x, int y);
            bool add(const Shape & shape, int x, int y);

    };

#endif//STRUCTURE_H_
