#include "constantes.h"

#ifndef SHAPES_H_
#define SHAPES_H_

    const unsigned int sI = 4, cI = 2, xInitI = 0, yInitI = 1;
    const shape iShape = {
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
    
    const unsigned int sO = 2, cO = 1, xInitO = 0, yInitO = 0;   
    const shape oShape = {
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
    
    const unsigned int sL = 3, cL = 4, xInitL = 0, yInitL = 1;
    const shape lShape = {
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
    
    const unsigned int sJ = 3, cJ = 4, xInitJ = 0, yInitJ = 1;
    const shape jShape = {
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
