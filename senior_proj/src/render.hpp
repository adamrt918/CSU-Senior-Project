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
        const int START_PAGE_TEXTURES = 2;
        const int TASKBAR_TEXTURES = 2;
        const int PLAYER_TEXTURES = 3;
        const int MAIN_MENU_TEXTURES = 4; // 1 texture for each clickable word
        const int TUTORIAL_TEXTURES = 12; // textures for individual highlights and going back to the main menu
        const int QUOTATION_PAGE_TEXTURES = 3;
        const int CHOICE_PAGE_TEXTURES = 4;
        const int POST_CHOICE_PAGE_TEXTURES = 3;
        const int TEXT_PAGE_TEXTURES = 2;
        const int OUTCOME_PAGE_TEXTURES = 2;
        const int VERSE_PAGE_TEXTURES = 2;
        const int END_CHAPTER_PAGE_TEXTURES = 2;    

        //Constructor Destructor.
        Render(LTexture* textures, Window* window);
        ~Render();

        //Renderers for the different pages
        void startPageRenderer(SDL_Renderer* renderer);
        void muteButtonRenderer(bool unMute, SDL_Renderer* renderer, SDL_Rect* MUTE_BUTTON_SPRITES, LTexture* MUTE_BUTTON);
        void timerRenderer(SDL_Renderer* renderer, SDL_Rect* timerSprites, LTexture* timerTexture, int seconds);
        void mainMenuRenderer(SDL_Renderer* renderer);
        void tutorialRenderer(SDL_Renderer* renderer);
        void taskBarRenderer(SDL_Renderer* renderer, LTexture* TASKBAR);
        void playerBarRenderer(SDL_Renderer* renderer, LTexture* PLAYER_STATS);
        void quotationPageRenderer(SDL_Renderer* renderer);
        void choicePageRenderer(SDL_Renderer* renderer, Player* gamer, bool isOut); //Renders the choice page based on sanity   
        void postChoicePageRenderer(SDL_Renderer* renderer);
        void outcomePageRenderer(SDL_Renderer* renderer);
        void versePageRenderer(SDL_Renderer* renderer);
        void textPageRenderer(SDL_Renderer* renderer);

    private:
        int totalHeight(int tNum);

        //Validates that text remains on screen
        int validateX(int xx, int textureWidth);
        int validateY(int yy, int textureHeight);
        
        LTexture* textures;
        Player* gamer;
        Window* dms;
};

#include "render.cpp"
#endif