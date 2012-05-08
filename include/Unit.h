#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

    #include "Shape.h"

    class Unit {

        private:
            int x;
            int y;
            unsigned int form;
            const Shape * shape;

        public:
            Unit(const Shape & shape);
            void change(const Shape & shape);

            void left();
            void right();
            void fall();
            void bottom();
            void rotate();
            bool checkX();

            const Shape & getShape() const ;
            int getX() const ;
            int getY() const ;
            int getForm() const ;
    };

    bool blitInit(Surface & surface, const Unit & unit);
    bool blit(Surface & surface, const Unit & unit);

#endif // UNIT_H_INCLUDED
