#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <../ltexture.hpp>

class Timer
{
    public:
        //constructor destructor
        Timer();
        ~Timer();

        //Load in the texture for timer
        bool loadTimer(SDL_Renderer* gRenderer);

        //This is what the timer does
        void timerEvents();

        //Getters and setters
        LTexture* getTimerTexture();
        SDL_Rect* getTimerSprites();
        int getSeconds();
        void setSeconds(int count);
        bool isOut();

    private:
        LTexture timerTexture;
        SDL_Rect timerSprites[11];
        int seconds;
        Uint32 startTime = SDL_GetTicks();
        Uint32 deltaTime = 0;
        Uint32 countdownInterval = 1000; //1 second
        bool outOfTime;
};

#include "timer.cpp"
#endif