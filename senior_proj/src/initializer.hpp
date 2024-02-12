#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;


class Initializer
{

    public:

        //Variable to hold the screen dimensions
        SDL_DisplayMode dm;

        Initializer();
        ~Initializer();
        bool init();
        bool loadMedia();
        SDL_DisplayMode getScreen();
        

    private:
        SDL_DisplayMode getDisplay();
};

#include "initializer.cpp"

#endif