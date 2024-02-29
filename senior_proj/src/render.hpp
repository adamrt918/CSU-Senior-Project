#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <../ltexture.hpp>
#include <../player.hpp>
#include <../window.hpp>

class Render
{
    public:
    //Textures Per Page
    static const int TASKBAR_TEXTURES = 2;
    static const int PLAYER_TEXTURES = 3;
    static const int START_PAGE_TEXTURES = 1;
    static const int MAIN_MENU_TEXTURES = 4; // 1 texture for each clickable word
    static const int TUTORIAL_TEXTURES = 12; // textures for individual highlights and going back to the main menu
    static const int QUOTATION_PAGE_TEXTURES = 3;
    static const int CHOICE_PAGE_TEXTURES = 4;
    static const int POST_CHOICE_PAGE_TEXTURES = 3;
    static const int TEXT_PAGE_TEXTURES = 2;
    static const int OUTCOME_PAGE_TEXTURES = 2;
    Render(LTexture* textures);
    ~Render();

    //Renderers for the different pages
    void choicePageRenderer(int chooser, SDL_Renderer* renderer, Player* gamer); //Renders the choice page based on sanity    

private:
    int totalHeight(int tNum);
    LTexture* textures;
    Player* gamer;
    Window dimensions;
};

#include "render.cpp"
#endif