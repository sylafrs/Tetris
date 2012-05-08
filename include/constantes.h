#ifndef CONSTANTES_H_
#define CONSTANTES_H_

    const int windowWidth = 300;
    const int windowHeight = 400;
    const char windowTitle[] = "Tetris";

    const int maxShapeWidth = 4;
    const int maxShapeHeight = 4;
    const int maxShapeForms = 4;

    const int squareSize = 10;

    const int wGrid = 10;
    const int hGrid = 20;

    typedef bool shape [maxShapeForms][maxShapeHeight][maxShapeWidth];
    
    #include "shapes.h"

#endif//CONSTANTES_H_
