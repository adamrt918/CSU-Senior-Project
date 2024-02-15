#ifdef PAGES_H
#define PAGES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;


// Class to hold the individual events for different pages 
class Pages
{
    public:

    //Constructor
    Pages();
    //Destructor
    ~Pages();
    
    //Loads the textures needed for the main menu
    bool mediaLoader(int newPage);
    bool events();

    private:
        int num;
};

#include "pages.cpp"
#endif