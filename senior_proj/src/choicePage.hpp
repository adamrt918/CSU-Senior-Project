#ifndef CHOICEPAGE_H
#define CHOICEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <../ltexture.hpp>
#include <../player.hpp>
#include <../window.hpp>
#include <string>
#include <iostream>

using namespace std;

class ChoicePage
{
    public:
        const int CHOICE_PAGE_TEXTURES = 4;
        static const int GAME_PAGE_2 = 20;
        const int GAME_PAGE_6 = 60;
        const string GAME_PAGE_2_WORDS[4] = {"    \"What does it mean to be a man?\" My father asked me, a young 17-year-old boy preparing to embark upon the adventures only found on the precipice of manhood. ",
        "\"Military service.\"", 
        "\"There\'s no such thing.\"", 
        "\"I don\'t know.\""};

        //Colors
        const SDL_Color BACKGROUND_COLOR = {0, 0, 0, SDL_ALPHA_OPAQUE}; //Background color black
        const SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
        const SDL_Color TAN = {210, 180, 140, SDL_ALPHA_OPAQUE};
        const SDL_Color GREY = {128, 128, 128, SDL_ALPHA_OPAQUE};
        const SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};

        //Font sizes
        //Text sizes
        const int HEADING_1 = 72;
        const int HEADING_2 = 48;
        const int HEADING_3 = 36;
        const int QUOTATION = 18;
        const int WRITING = 24;


        ChoicePage();
        ChoicePage(int txtrNum, int pageNum, Player player);
        ~ChoicePage();

        bool loadMedia(LTexture* textures, SDL_Renderer* gRenderer);

    private:
        int texture; // the number of textures to be loaded.
        int pgNum; //The page number of the choices to be loaded.
        Player gamer; //Holds the gamer's stats
        // LTexture* textures; //Pointer to an array of textures to be loaded.
        SDL_DisplayMode dms;

};

#include "choicePage.cpp"
#endif