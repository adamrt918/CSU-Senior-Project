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
        const SDL_Color BACKGROUND_COLOR = {0, 0, 0, SDL_ALPHA_OPAQUE}; //Background color black
        const SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
        const SDL_Color TAN = {210, 180, 140, SDL_ALPHA_OPAQUE};
        const SDL_Color GREY = {128, 128, 128, SDL_ALPHA_OPAQUE};
        const SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};
        
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

        //Overload that includes wrap length
        bool loadFromRenderedText(SDL_Renderer* gRenderer, std::string textureText, SDL_Color textColor, int wrapLength);
        
        //Deallocates texture
        void free();
    
        //Renders texture at given point
        void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer);

        //Checks if the mouse is over the text rectangle
        bool isMouseOver(SDL_Rect rect); 
        
        //Gets the rectangle
        SDL_Rect getRect();

        //Gets image dimensions
        int getWidth();
        int getHeight();

        //Gets the word
        string getWord();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //A locally used rectangle
        SDL_Rect lRect;
        
        //Image dimensions
        int mWidth;
        int mHeight;

        //Word of the texture being displayed.
        string word;
};

#include "ltexture.cpp"
#endif