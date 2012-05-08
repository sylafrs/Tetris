#include "constantes.h"

#ifndef SHAPE_H_
#define SHAPE_H_

    #include "Surface.h"

    class Shape {
        private:
            const Surface & surface;
            const shape & shapeArray;

            const unsigned int size;
            const unsigned int cForms;
            const unsigned int initX;
            const unsigned int initY;

        public:
            Shape(  const Surface & surface,
                    const shape & shapeArray,
                    unsigned int size, unsigned int cForms,
                    unsigned int initX, unsigned int initY);

            virtual ~Shape();

            const Surface & getSurface() const;
            bool check(unsigned int x, unsigned int y, unsigned int num) const;
            unsigned int getSize() const;
            unsigned int getCForms() const;
            unsigned int getInitX() const;
            unsigned int getInitY() const;

            bool checkX(int & x, int max, unsigned int num) const;
    };

    bool blitInit(Surface & surface, const Shape & shape,
                  unsigned int x, unsigned int y);

    bool blit(Surface & surface, const Shape & shape,
              unsigned int x, unsigned int y, unsigned int num);

#endif//SHAPE_H_
