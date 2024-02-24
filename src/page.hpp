#ifndef PAGE_H
#define PAGE_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <../ltexture.hpp>
#include <vector>

using namespace std;

class Page{
    public:
        Page(const int newPgNum, const int newTxtNum, const string* newWords, LTexture* newTextures);
        ~Page();

        void mainMenuRenderer(SDL_DisplayMode dimensions, SDL_Renderer* renderer);
        void taskBarRenderer();
        void playerBarRenderer();
        void tutorialRenderer();
        void quotationPageRenderer();
        void choicePageRenderer();
        void postChoicePageRenderer();
        void textPageRenderer();

        //Getters and Setters
        int getPgNum();
        void setPgNum(int newPgNum);

        int getTxtNum();
        void setTxtNum(int newTxtNum);

        string* getPgWords();
        void setPgWords(string* newWords);

        LTexture* getTextures();
        void setTextures(LTexture* newTexture);

    private:
        int pgNum;
        int txtNum;
        string* pgWords;
        LTexture* textures;
};

#include "page.cpp"
#endif