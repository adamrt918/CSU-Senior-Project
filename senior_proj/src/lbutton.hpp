#ifndef LBUTTON_H
#define LBUTTON_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <../ltexture.hpp>

//The mouse button
class LButton
{
    public:
        enum LButtonSprite
        {
            BUTTON_SPRITE_MOUSE_OUT = 0,
            BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
            BUTTON_SPRITE_MOUSE_DOWN = 2,
            BUTTON_SPRITE_TOTAL = 3
        };
        //Initializes internal variables
        LButton();

        //Sets top left position
        void setPosition( int x, int y );

        //Handles mouse event
        void handleEvent( SDL_Event* e );
    
        //Shows button sprite
        void render(LTexture texture, SDL_Rect* gSpriteClips, SDL_Renderer* gRenderer);

    private:
        //Top left position
        SDL_Point mPosition;

        //Currently used global sprite
        LButtonSprite mCurrentSprite;

        int buttonW;
        int buttonH;
};

#include "lbutton.cpp"
#endif