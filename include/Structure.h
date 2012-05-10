#ifndef STRUCTURE_H_
#define STRUCTURE_H_

    #include "Surface.h"
    #include <vector>
    #include <list>

    class Unit;
    class Shape;

    typedef std::vector<const Surface *> line;

    class Structure {

        private:
            std::list<line> structure;
            line & getLine(unsigned int n);

        public:
            bool check(const Unit & unit) const ;
            void add(const Unit & unit);
            bool check(const Shape & shape, int x, int y, int form) const ;
            void add(const Shape & shape, int x, int y, int form);

            unsigned int getLineCount() const ;
            const Surface * get(unsigned int line, unsigned int column) const ;
            const line & getLine(unsigned int n) const;
    };

    void blit(Surface & surface, const Structure & structure);

    #include "Unit.h"
    #include "Shape.h"

#endif//STRUCTURE_H_
