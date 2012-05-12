#ifndef CONSTANTES_H_
#define CONSTANTES_H_

    const int windowWidth = 300;
    const int windowHeight = 400;
    const char windowTitle[] = "Tetris";
    
    const int initShapeWidth = 4;
    const int initShapeHeight = 2;
    const int xPrev = 50;
    const int yPrev = 130;

    const int maxShapeWidth = 4;
    const int maxShapeHeight = 4;
    const int maxShapeForms = 4;

    const int squareSize = 10;

    const int xGrid = 20;
    const int yGrid = 150;
    const int wGrid = 10;
    const int hGrid = 20;
    const int initX = 3;
    const int initY = 0;
    
    const int fallSpeedInit = 1000;
    const int fastFallSpeed = 50;
    const int moveSpeed = 100;
    
    const int minFrameTime = 30; // = 60/maxFPS

    typedef bool shape [maxShapeForms][maxShapeHeight][maxShapeWidth];

    enum delimType {
        MIN_COL, MAX_COL, MIN_LIN, MAX_LIN, D_SIZE
    };
    typedef int delims [maxShapeForms][D_SIZE];

    #include "shapes.h"

#endif//CONSTANTES_H_
