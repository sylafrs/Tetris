#ifndef STRUCTURE_H_
#define STRUCTURE_H_

    #include "Unit.h"
    #include "Surface.h"
    #include <list>
    #include <vector>

    class Structure {

        private:
            std::list<std::vector<const Surface *> > structure;

        public:
            bool check(const Unit & unit);
            bool add(const Unit & unit);
            bool check(const Shape & shape, int x, int y, int form);
            bool add(const Shape & shape, int x, int y, int form);

    };

#endif//STRUCTURE_H_
