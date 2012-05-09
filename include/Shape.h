#include "constantes.h"

#ifndef SHAPE_H_
#define SHAPE_H_

    #include "Surface.h"

    class Structure;

    class Shape {
        private:
            const Surface & surface;
            const shape & shapeArray;

            delims maxMinArray;

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
            bool get(unsigned int x, unsigned int y, unsigned int num) const;
            unsigned int getSize() const;
            unsigned int getCForms() const;
            unsigned int getInitX() const;
            unsigned int getInitY() const;

            int getMaxLine(unsigned int form) const;
            int getMinLine(unsigned int form) const;
            int getMaxColumn(unsigned int form) const;
            int getMinColumn(unsigned int form) const;

            unsigned int getMaxInColumn(unsigned int c, unsigned int form) const ;
            unsigned int getMinInLine(unsigned int l, unsigned int form) const ;
            unsigned int getMaxInLine(unsigned int l, unsigned int form) const ;

            void checkSides(int & x, int & y, int maxX, int maxY, unsigned int num) const;
    };

    #include "Structure.h"

    bool blit(Surface & surface, const Shape & shape,
              unsigned int x, unsigned int y, unsigned int num);

#endif//SHAPE_H_
