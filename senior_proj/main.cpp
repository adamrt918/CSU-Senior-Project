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

using namespace std;


int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Get the user's primary display size
    SDL_DisplayMode dm;
    if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
        printf("Unable to get display mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("Full Size Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, SDL_WINDOW_FULLSCREEN);
    if (window == nullptr) {
        printf("Unable to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Color backgroundColor = { 0, 0, 0 }; // Black color (R, G, B)
    SDL_Color textColor = { 255, 255, 255 }; // White color (R, G, B)

    // Set background color
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255); // Alpha set to full

    TTF_Font* font = TTF_OpenFont("resources/Abadi_MT_Std.ttf", 28);
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, SDL!", textColor);
    if (surface == nullptr) {
        std::cerr << "Failed to create surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Rect textRect;
    textRect.x = 100;
    textRect.y = 100;
    textRect.w = surface->w;
    textRect.h = surface->h;

    // Clear the screen
    SDL_RenderClear(renderer);

    // Render the text
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Present the renderer
    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}