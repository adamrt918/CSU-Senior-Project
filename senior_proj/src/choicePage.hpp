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
        static const int OUTCOME_PAGE = 4;
        static const int GAME_PAGE_2 = 20;
        static const int GAME_PAGE_3_1 = 31;
        static const int GAME_PAGE_3_2 = 32;
        static const int GAME_PAGE_3_3 = 33;
        static const int GAME_PAGE_6 = 60;
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
        ChoicePage(int txtrNum, Player* player);
        ChoicePage(Player* player);
        ~ChoicePage();

        //Loads the page media
        bool loadMedia(LTexture* textures, SDL_Renderer* gRenderer, int pgNum);

        int choicePageEvents(int pgNum, SDL_Color* textColor, LTexture* textures, SDL_Event e, SDL_Renderer* renderer);

    private:
        int texture; // the number of textures to be loaded.
        Player* gamer; //Holds the gamer's stats
        SDL_DisplayMode dms; //Holds the monitor dimensions
        int coward = -1; //Holds the most cowardly choice
        Window dimensions;
        struct Choices{
            string text;
            int bounds[3][2];
            int statChange[3]; //0 health, 1 sanity, 2 reputation
            enum choiceType {Heroic, Average, Cowardly};
            choiceType courageLevel;
        };
        //A max of 3 choices per page
        Choices choice[3];

        //Chooses which media should be loaded.
        int chooser();

};

#include "choicePage.cpp"
#endif