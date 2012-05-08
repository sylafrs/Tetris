#ifndef INPUT_H_
#define INPUT_H_

    #include <SDL/SDL.h>

    class Input {
        public:
            bool key[SDLK_LAST];
            int mousex, mousey;
            int mousexrel, mouseyrel;
            bool mousebuttons[8];
            bool quit;

            Input();
            virtual ~Input();
            void update();
    };

#endif//INPUT_H_
