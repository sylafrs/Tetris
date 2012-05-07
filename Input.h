#ifndef INPUT_H_
#define INPUT_H_

    #include <SDL/SDL.h>

    class Input {
        public:
            char key[SDLK_LAST];
            int mousex, mousey;
            int mousexrel, mouseyrel;
            char mousebuttons[8];
            char quit;

            Input();
            virtual ~Input();
            void update();
    };

#endif//INPUT_H_
