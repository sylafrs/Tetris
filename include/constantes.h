#ifndef CONSTANTES_H_
#define CONSTANTES_H_
   
    const int maxShapeWidth = 4;
    const int maxShapeHeight = 4;
    const int maxShapeForms = 4;
        
    typedef bool shape [maxShapeForms][maxShapeHeight][maxShapeWidth];

    enum delimType {
        MIN_COL, MAX_COL, MIN_LIN, MAX_LIN, D_SIZE
    };
    typedef int delims [maxShapeForms][D_SIZE];

#endif//CONSTANTES_H_
