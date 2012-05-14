#include "../include/Jeu.h"
#include "../include/SDL_Object.h"
#include "../include/constantes.h"
#include "../include/shapes.h"
#include "../include/Surface.h"

#include <cmath>
#include <iostream>

using namespace std;

void speedUp(int & current) {
    current = sqrt((current*current)-100);
}

#ifndef __LINUX__
int main(int argc, char * argv[]) {
#else
int main() {
#endif

    const int windowWidth = 300;
    const int windowHeight = 400;
    const char windowTitle[] = "Tetris";

    try {
        SDL sdl(windowTitle, windowWidth, windowHeight);
        Video & video = sdl.getVideo();

        Jeu tetris(sdl);

        ImageSurface  rouge(video, "../imgs/rouge.bmp");
        ImageSurface   bleu(video, "../imgs/bleu.bmp");
        ImageSurface   vert(video, "../imgs/vert.bmp");
        ImageSurface  jaune(video, "../imgs/jaune.bmp");
        ImageSurface orange(video, "../imgs/orange.bmp");
        ImageSurface   cyan(video, "../imgs/cyan.bmp");
        ImageSurface violet(video, "../imgs/violet.bmp");

        tetris.addShape(rouge,  zShape, sZ, cZ, xInitZ, yInitZ);
        tetris.addShape(bleu,   jShape, sJ, cJ, xInitJ, yInitJ);
        tetris.addShape(vert,   sShape, sS, cS, xInitS, yInitS);
        tetris.addShape(jaune,  oShape, sO, cO, xInitO, yInitO);
        tetris.addShape(orange, lShape, sL, cL, xInitL, yInitL);
        tetris.addShape(cyan,   iShape, sI, cI, xInitI, yInitI);
        tetris.addShape(violet, tShape, sT, cT, xInitT, yInitT);

        tetris.setEmpty("../imgs/vide.bmp");
        tetris.setBackground("../imgs/fond.bmp");
        tetris.setBoomAnimation("../imgs/boom.bmp", 10, 3, 100);
        tetris.setBoomSound("../snd/boom.wav");

        tetris.play();
    }
    catch(const Exception & e) {
        cerr << e << endl;
    }

    return 0;
}
