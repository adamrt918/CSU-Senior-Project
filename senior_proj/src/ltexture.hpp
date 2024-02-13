#ifndef LTEXTURE_H
#define LTEXTURE_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;


//Texture wrapper class
class LTexture
{

    public:
        //Globally used font
        TTF_Font* gFont = NULL;

        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
        
        //Creates image from font string
        bool loadFromRenderedText(SDL_Renderer* gRenderer, std::string textureText, SDL_Color textColor );
        
        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer);

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

#include "ltexture.cpp"
#endif