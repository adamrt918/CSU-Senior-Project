#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include <../ltexture.hpp>
#include <iostream>
#include <vector>
#include <../initializer.hpp>

using namespace std;

//Black background color {r, g, b}
const SDL_Color BACKGROUND_COLOR = {0, 0, 0};

//White text color {r, g, b}
const SDL_Color TEXT_COLOR = {255, 255, 255};

//Monitor dimensions for fullscreen
SDL_DisplayMode dm;

//SDL window
SDL_Window* window;

//Holds texture being rendered to the window.
SDL_Renderer* renderer; 

//ttf font type
TTF_Font* font;

//Holds raw pixel data/metadata
SDL_Surface* surface;

//Texture to be rendered at a given time
SDL_Texture* texture;

//Text box
SDL_Rect textRect;



//Initialize various SDL libraries and pointers.
bool init();

//Load in necessary media for font, images, etc.
bool loadMedia();

//Close out all the initialized SDL libraries and variables.
void close();

int main(int argc, char* args[]) {
  
    
    if (!init())
        return 1;
    if (!loadMedia())
        return 1;

    // // Clear the screen
    // SDL_RenderClear(renderer);

    // // Render the text
    // SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // // Present the renderer
    // SDL_RenderPresent(renderer);

    //Game flag
    bool gaming = true;

    //Event handler
    SDL_Event e;

    while (gaming) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                gaming = false;
            }
        }

        // Get text dimensions
        int textW, textH;
        SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

        //Calculate text position to be in the center of the screen
        int textX = (dm.w - textW) / 2;
        int textY = (dm.h - textH) / 2;

        // Clear screen
        SDL_RenderClear(renderer);

        // Render text
        SDL_Rect renderQuad = {textX, textY, textW, textH};
        SDL_RenderCopy(renderer, texture, NULL, &renderQuad);

        // Update screen
        SDL_RenderPresent(renderer);
    }
    close();
    return 0;
}

bool init()
{
    //Initialize everything in the SDL Library
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    
        
    //Initialize the ttf SDL extension
    if (TTF_Init() < 0)
        return false;

    // Get the user's primary display size
    if (SDL_GetCurrentDisplayMode(0, &dm) != 0) 
    {
        printf("Unable to get display mode: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // Create an SDL window
    window = SDL_CreateWindow("Full Size Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, SDL_WINDOW_FULLSCREEN);
    if (window == nullptr) {
        printf("Unable to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set background color
    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255); // Alpha set to full


    return true;
}

bool loadMedia()
{
    font = TTF_OpenFont("resources/Abadi_MT_Std.ttf", 28);
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
        
    surface = TTF_RenderText_Solid(font, "Hello, SDL!", TEXT_COLOR);
    if (surface == nullptr) {
        std::cerr << "Failed to create surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}


void close()
{    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

