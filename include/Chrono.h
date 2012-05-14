#ifndef CHRONO_H_
#define CHRONO_H_

    #include "SDL/SDL.h"

    class Chrono {
    
        private:
            Uint32 prevTime;

        public:
            Chrono();
            bool check(Uint32 delay);
            void wait(Uint32 delay);
            void reset();
    };

#endif//CHRONO_H_
