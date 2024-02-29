#ifdef CHOICEPAGE_H

//Constructor -- overloaded when I want to initialize
ChoicePage::ChoicePage(){
}
ChoicePage::ChoicePage(int txtrNum, int pageNum, Player* player){
    pgNum = pageNum;
    texture = txtrNum;
    gamer = player;
}
ChoicePage::ChoicePage(Player* player){
    gamer = player;
}

//Destructor
ChoicePage::~ChoicePage(){
    delete gamer;
}

bool ChoicePage::loadMedia(LTexture* textures, SDL_Renderer* gRenderer, int pgNum){
    Window dimensions;
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
            
            //If the player is not insane, load the normal choices
            if (!gamer->getInsane())
            {
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
            }
            //If the player is insane, only load the cowardly choice
            else{
                int coward = chooser();
                textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[1].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[1].loadFromRenderedText(gRenderer, choice[coward].text, TAN, dimensions.w() / 1.3))
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

#endif