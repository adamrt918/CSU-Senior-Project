#ifndef PAGES_H
#define PAGES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


// Class to hold the individual events for different pages 
class Pages
{
    public:
    
    //Constructor
    Pages(int pages, int textures, string word[]);
    //Destructor
    ~Pages();
    
    //Loads the textures needed for the main menu
    bool mediaLoader(int newPage);
    bool events();

    void setPageNum(int page);
    int getPageNum();

    void setTextureNum(int texture);
    int getTextureNum();

    void setWords(string word);
    vector<string> getWords();

    private:
        int pageNum;
        int textureNum;
        vector<string> words;
};

#include "pages.cpp"
#endif