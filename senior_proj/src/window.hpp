#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <../ltexture.hpp>
#include <../player.hpp>
#include <string>
#include <iostream>

class Window{
    public:
    Window();
    ~Window();

    bool initWindow();

    int w();
    int h();

    // getDimension
    private:
    SDL_DisplayMode dimensions;

};

#include "window.cpp"
#endif