#ifndef CHOICE_H
#define CHOICE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

//Choice class for the type of choice and games functions used.
class Choice
{
    public:
        const int HERO = 0;
        const int NORMAL = 1;
        const int COWARD = 2;

        Choice();
        ~Choice();

        
    private:
        
        //Choice type
        int choiceType;

};

#include "choice.cpp"
#endif