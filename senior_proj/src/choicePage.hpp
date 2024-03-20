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
        /*Page Numbers*/
        static const int NULL_PAGE = -1;
        static const int START_PAGE = 0;
        static const int MAIN_MENU_PAGE = 1;
        static const int TUTORIAL_PAGE = 2;
        static const int SURVEY_PAGE = 3;
        static const int OUTCOME_PAGE = 4;
        static const int GAME_PAGE_1 = 10;
        static const int GAME_PAGE_2 = 20;
        static const int GAME_PAGE_3_1 = 31;
        static const int GAME_PAGE_3_2 = 32;
        static const int GAME_PAGE_3_3 = 33;
        static const int GAME_PAGE_4 = 40;
        static const int GAME_PAGE_5 = 50;
        static const int GAME_PAGE_6 = 60;
        static const int GAME_PAGE_7_1 = 71;
        static const int GAME_PAGE_7_2 = 72;
        static const int GAME_PAGE_7_3 = 73;
        static const int GAME_PAGE_8 = 80;
        static const int GAME_PAGE_9 = 90;
        static const int GAME_PAGE_10 = 100;
        static const int GAME_PAGE_11_1 = 111;
        static const int GAME_PAGE_11_2 = 112;
        static const int GAME_PAGE_11_3 = 113;
        static const int GAME_PAGE_12 = 120;
        static const int GAME_PAGE_13 = 130;
        static const int GAME_PAGE_14_1 = 141;
        static const int GAME_PAGE_14_2 = 142;
        static const int GAME_PAGE_14_3 = 143;
        static const int GAME_PAGE_15 = 150;
        static const int GAME_PAGE_16 = 160;
        static const int GAME_PAGE_17 = 170;
        static const int GAME_PAGE_18 = 180;

        static const int CHOICE_PAGE_TEXTURES = 4;

        /* Words per page */
        const string GAME_PAGE_2_WORDS[CHOICE_PAGE_TEXTURES] = {"    \"What does it mean to be a man?\" My father asked me, a young 17-year-old boy preparing to embark upon the adventures only found on the precipice of manhood. ",
            "\"Military service.\"", 
            "\"There\'s no such thing.\"", 
            "\"I don\'t know.\""
        };
        const string GAME_PAGE_6_WORDS[CHOICE_PAGE_TEXTURES] = {"\"Where were you?\" the sergeant asks. ",
            "\"I couldn't find my belt, sergeant.\"",
            "\"I was sleeping and didn't set an alarm.\"",
            "\"I don't want to be a ranger anymore. I quit."};
        const string GAME_PAGE_10_WORDS[CHOICE_PAGE_TEXTURES] = {
            "    I spent the whole night typing in tiny font to finish this essay. The question my Dad had asked me was at the forefront of my mind. What have I been doing all this time? I'm going through my time in service, but do I have what it takes to be a man?\n" 
            "    The answer I settled on was:\n",
            "responsibility, accountability, discipline, and love.",
            "Manhood doesn't matter. Just how good of a person you are.",
            "Following tenants of love, mercy, and grace towards fellow mankind."
        };
        const string GAME_PAGE_13_WORDS[CHOICE_PAGE_TEXTURES] = {"Troubled, I thought about my next move.",
            "I stood back up and started sprinting towards the white light, completely disregarding a direct order.",
            "I remained laying on the ground, waiting to see what my team leader would do next.",
            "I took a knee and tried to convince the corporal that something was wrong."
        };
        const string END_CHAPTER_PAGE_WORDS[CHOICE_PAGE_TEXTURES] = {"You have finished the chapter, how will you continue?", 
            "Roll for health restoration", 
            "Roll for sanity restoration",
            "Roll for reputation increase"        
        };
        
        //Colors
        const SDL_Color BACKGROUND_COLOR = {0, 0, 0, SDL_ALPHA_OPAQUE}; //Background color black
        const SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
        const SDL_Color TAN = {210, 180, 140, SDL_ALPHA_OPAQUE};
        const SDL_Color GREY = {128, 128, 128, SDL_ALPHA_OPAQUE};
        const SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};

        //Font sizes
        const int HEADING_1 = 72;
        const int HEADING_2 = 48;
        const int HEADING_3 = 36;
        const int QUOTATION = 18;
        const int WRITING = 24;


        ChoicePage(Player* player, LTexture* textures);
        ~ChoicePage();

        //Loads the page media
        bool loadMedia(SDL_Renderer* gRenderer, int pgNum);

        //Chooses what to do based on the choice page
        int choicePageEvents(int currentPage, SDL_Color* textColor, SDL_Event e, SDL_Renderer* renderer);

        //Chooses which media should be rendered in case of insanity.
        int chooseInsane();

        //Gets the 3 stat changes for the decision
        int* getStatChange();

        //Gets the stored page
        int getStorePage();
        void setStorePage(int sp);

        //Getters and setters for width and height
        int getW();
        void setW(int width);
        int getH();
        void setH(int height);


    private:
        int texture; // the number of textures to be loaded.
        Player* gamer; //Holds the gamer's stats
        int coward = -1; //Holds the most cowardly choice
        int decision; //Holds the player decision
        int storePage; //Stores the page to display after the outcome
        int w;
        int h;
        LTexture* textures;
        struct Choices{
            string text;
            int bounds[3][2];
            int statChange[3]; //0 health, 1 sanity, 2 reputation
            enum ChoiceType {Heroic, Average, Cowardly};
            ChoiceType courageLevel;
        };
        //A max of 3 choices per page
        Choices choice[3];
};

#include "choicePage.cpp"
#endif