#include "constantes.h"

#ifndef SHAPES_H_
#define SHAPES_H_

    const unsigned int sLine = 4, cLine = 2, xInitLine = 0, yInitLine = 1;
    const shape lineShape = {
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        }
    }; 
    
    const unsigned int sSquare = 2, cSquare = 1, xInitSquare = 0, yInitSquare = 0;   
    const shape squareShape = {
        {
            {1, 1},
            {1, 1}
        }
    };
    
    const unsigned int sT = 3, cT = 4, xInitT = 0, yInitT = 1;
    const shape tShape = {       
        {
            {0, 0, 0},
            {1, 1, 1},
            {0, 1, 0}
        },
        {
            {0, 1, 0},
            {0, 1, 1},
            {0, 1, 0}
        },
        {
            {0, 0, 0},
            {0, 1, 0},
            {1, 1, 1}
        },
        {
            {0, 1, 0},
            {1, 1, 0},
            {0, 1, 0}
        }
    };
    
    const unsigned int sLongL = 3, cLongL = 4, xInitLongL = 0, yInitLongL = 1;
    const shape longLShape = {
        {
            {0, 0, 0},
            {1, 1, 1},
            {1, 0, 0}
        },
        {
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 1}
        },
        {
            {0, 0, 0},
            {0, 0, 1},
            {1, 1, 1}
        },
        {
            {1, 1, 0},
            {0, 1, 0},
            {0, 1, 0}
        }
    };
    
    const unsigned int sLargeL = 3, cLargeL = 4, xInitLargeL = 0, yInitLargeL = 1;
    const shape largeLShape = {
        {
            {0, 0, 0},
            {1, 1, 1},
            {0, 0, 1}
        },
        {
            {0, 1, 1},
            {0, 1, 0},
            {0, 1, 0}
        },
        {
            {0, 0, 0},
            {1, 0, 0},
            {1, 1, 1}
        },
        {
            {0, 1, 0},
            {0, 1, 0},
            {1, 1, 0}
        }
    };
    
    const unsigned int sS = 3, cS = 2, xInitS = 0, yInitS = 1;
    const shape sShape = {
        {
            {0, 0, 0},
            {0, 1, 1},
            {1, 1, 0}
        },
        {
            {1, 0, 0},
            {1, 1, 0},
            {0, 1, 0}
        }
    };
    
    const unsigned int sZ = 3, cZ = 2, xInitZ = 0, yInitZ = 1;
    const shape zShape = {
        {
            {0, 0, 0},
            {1, 1, 0},
            {0, 1, 1}
        },
        {
            {0, 0, 1},
            {0, 1, 1},
            {0, 1, 0}
        }
    };  

#endif//SHAPES_H_
