#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


// Class to hold the individual events for different pages 
class Player
{
    public:
    Player();
    ~Player();
    
    int getHealth();
    void setHealth();

    int getSanity();
    void setSanity();

    int getRep();
    void setRep();

    private:
        int health;
        int sanity;
        int reputation;
};

#include "player.cpp"
#endif