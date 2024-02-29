#ifdef CHOICEPAGE_H

//Constructor -- overloaded when I want to initialize
ChoicePage::ChoicePage(){
}
ChoicePage::ChoicePage(int txtrNum, Player* player){
    texture = txtrNum;
    gamer = player;
}
ChoicePage::ChoicePage(Player* player, LTexture* textures){
    gamer = player;
    this->textures = textures;
}

//Destructor
ChoicePage::~ChoicePage(){
    delete gamer;
}

bool ChoicePage::loadMedia(SDL_Renderer* gRenderer, int pgNum){
    switch (pgNum){
        case GAME_PAGE_2:
            //Load the game text
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }  
            if (!textures[0].loadFromRenderedText(gRenderer, GAME_PAGE_2_WORDS[0], GREY, dimensions.w() / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }          

            //Instance the possible choices
            for (int i = 0; i < 3; i++){
                choice[i].text = GAME_PAGE_2_WORDS[i + 1];
                if (i == 0){
                    choice[i].courageLevel = Choices::Heroic;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -1; //Lower bound for sanity
                    choice[i].bounds[1][1] = 0; //Upper bound for sanity
                    choice[i].bounds[2][0] = 0; //Lower bound for reputation
                    choice[i].bounds[2][1] = 2; //Upper bound for reputation
                }
                else if ( i == 1){
                    choice[i].courageLevel = Choices::Cowardly;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -3; //Lower bound for sanity
                    choice[i].bounds[1][1] = -1; //Upper bound for sanity
                    choice[i].bounds[2][0] = -2; //Lower bound for reputation
                    choice[i].bounds[2][1] = 0; //Upper bound for reputation
                }
                else 
                {    
                    choice[i].courageLevel = Choices::Average;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -2; //Lower bound for sanity
                    choice[i].bounds[1][1] = 0; //Upper bound for sanity
                    choice[i].bounds[2][0] = -1; //Lower bound for reputation
                    choice[i].bounds[2][1] = 0; //Upper bound for reputation
                }
            }
            texture = CHOICE_PAGE_TEXTURES;
            for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(gRenderer, choice[i - 1].text, TAN, dimensions.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case GAME_PAGE_6:
            break;
        default:
            break;
    } //End switch
    return true;
} //End function

int ChoicePage::chooser(){
    
    //Return the cowardly choice if the gamer is insane
    if (gamer->getInsane())
        for (int i = 0; i < 3; i++)
            if (choice[i].courageLevel == Choices::Cowardly)
                return i;
    return -1;
}

int ChoicePage::choicePageEvents(int pgNum, SDL_Color* textColor, SDL_Event e, SDL_Renderer* renderer){
    int newPage;
    int storePage;
    switch (pgNum){
        case GAME_PAGE_2:

            //Iterating over choice textures
            for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++)
            {
                if (textures[i].isMouseOver(textures[i].getRect())){
                    *textColor = GREY;
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                    if(e.type == SDL_MOUSEBUTTONDOWN && chooser() == -1)
                    { 
                        switch (choice[i].courageLevel){
                            case Choices::Heroic: 
                                newPage = OUTCOME_PAGE;
                                storePage = GAME_PAGE_3_1;

                                //iterating over each metric within each choice
                                for (int j = 0; j < 3; j++)
                                    choice[i].statChange[j] = gamer->random(choice[i].bounds[j]);
                                
                                //Set the new value with the change in stats
                                gamer->setHealth(gamer->getHealth() + choice[i].statChange[0]);
                                gamer->setSanity(gamer->getSanity() + choice[i].statChange[1]);
                                gamer->setRep(gamer->getRep() + choice[i].statChange[2]);
                                break;
                            //Cowardly, minus 1 to 3 sanity -- minus 0 to 2 reputation
                            case Choices::Cowardly:
                                newPage = OUTCOME_PAGE;
                                storePage = GAME_PAGE_3_2;
                                
                                //iterating over each metric within each choice
                                for (int j = 0; j < 3; j++)
                                    choice[i].statChange[j] = gamer->random(choice[i].bounds[j]);
                                
                                //Set the new value with the change in stats
                                gamer->setHealth(gamer->getHealth() + choice[i].statChange[0]);
                                gamer->setSanity(gamer->getSanity() + choice[i].statChange[1]);
                                gamer->setRep(gamer->getRep() + choice[i].statChange[2]);
                                break;
                            //Average - 0 to 2 sanity -- minus 0 to 1 reputation
                            case Choices::Average:
                                newPage = OUTCOME_PAGE;
                                storePage = GAME_PAGE_3_3;

                                //iterating over each metric within the choice
                                for (int j = 0; j < 3; j++)
                                    choice[i].statChange[j] = gamer->random(choice[i].bounds[j]);
                                
                                //Set the new value with the change in stats
                                gamer->setHealth(gamer->getHealth() + choice[i].statChange[0]);
                                gamer->setSanity(gamer->getSanity() + choice[i].statChange[1]);
                                gamer->setRep(gamer->getRep() + choice[i].statChange[2]);                             
                                break;
                            default:
                                break;
                        } //End Mouse button down events
                    } //end if statement for non insane                  
                }
                else
                {
                    *textColor = TAN;
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                }
                textures[i].loadFromRenderedText(renderer, choice[i - 1].text, *textColor, dimensions.w()/1.3);
            } //End the texture for loop
            break;
        default:
            break;
    } //End Page number switch

    return newPage;
}

#endif