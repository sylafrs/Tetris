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
            const unsigned int wGrid, hGrid;
            std::list<line> structure;

            line & getLine(unsigned int n);

        public:
            Structure(unsigned int wGrid, unsigned int hGrid);
            virtual ~Structure();

            unsigned int getHGrid() const;
            unsigned int getWGrid() const;

            bool allowLeft(const Unit & unit) const;
            bool allowRight(const Unit & unit) const;

            bool allowRotL(const Unit & unit) const;
            bool allowRotR(const Unit & unit) const;

            bool allowLeft(const Shape & shape, int x, int y, int form) const;
            bool allowRight(const Shape & shape, int x, int y, int form) const;

            bool allowRotL(const Shape & shape, int x, int y, unsigned int form) const;
            bool allowRotR(const Shape & shape, int x, int y, unsigned int form) const;

            bool check(const Unit & unit) const ;
            void add(const Unit & unit);
            bool check(const Shape & shape, int x, int y, int form) const ;
            void add(const Shape & shape, int x, int y, int form);

            bool checkLine(unsigned int l) const ;
            unsigned int checkLines() const ;
            void eraseFullLines() ;
            void clear();

            unsigned int getLineCount() const ;
            const Surface * get(unsigned int line, unsigned int column) const ;
            const line & getLine(unsigned int n) const;
    };

    void blit(Surface & surface, const Structure & structure);
    void blitLine(unsigned int l, Surface & surface, const Structure & structure);
    void blitLineOf(unsigned int l, Surface & surface, const Surface & square, const Structure & structure);

    #include "Unit.h"
    #include "Shape.h"

#endif//STRUCTURE_H_
