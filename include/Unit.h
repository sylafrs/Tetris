#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

    #include "Shape.h"

    class Structure;

    class Unit {

        private:
            int x;
            int y;
            unsigned int form;
            const Shape * shape;
            const Structure & structure;

            const unsigned int initX, initY; 

        public:
            Unit(const Structure & structure, unsigned int initX, unsigned int initY, const Shape & shape);
            void change(const Shape & shape);

            bool left();
            bool right();
            void fall();
            bool bottom();
            bool rotate();

            void check();
            void checkSides();

            const Shape & getShape() const ;
            int getX() const ;
            int getY() const ;
            int getForm() const ;
    };

    #include "Structure.h"

    bool blit(Surface & surface, const Unit & unit);

#endif // UNIT_H_INCLUDED
