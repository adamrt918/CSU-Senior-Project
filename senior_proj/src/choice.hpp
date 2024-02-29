#ifndef CHOICE_H
#define CHOICE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

//Choice class for the type of choice, the text, and the games functions used.
class Choice
{
    public:
        
        Choice();
        Choice(int type, string text, int* b[]);
        ~Choice();


        // Getters and setters
        int getChoiceType();
        void setChoiceType(int type);

        string getChoiceText();
        void setChoiceText(string response);

        int* getChoiceBounds();
        void setChoiceBounds(int metrics[][2]);

        bool getTextExists();
        void setTextExists();
        
    private:        
        int choiceType; //Choice type 0 is hero, 1 is average, 2 is cowardly
        string choiceText; //Holds the actual text to be rendered
        //[Health/Sanity/Rep][lower/upper]
        int choiceBounds[3][2]; // Holds the upper and lower bounds for each metric for random number selection

        bool textExists; //Holds whether or not text has been added to the choice.



};

#include "choice.cpp"
#endif