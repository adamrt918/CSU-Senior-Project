#ifdef CHOICEPAGE_H

//Constructor -- overloaded when I want to initialize
ChoicePage::ChoicePage(){
}
ChoicePage::ChoicePage(int txtrNum, int pageNum, Player player){
    pgNum = pageNum;
    texture = txtrNum;
    gamer = player;
}

//Destructor
ChoicePage::~ChoicePage(){}

bool ChoicePage::loadMedia(LTexture* textures, SDL_Renderer* gRenderer, int pgNum){
    Window dimensions;
    switch (pgNum){
        case GAME_PAGE_2:
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

//CHECK TO SEE IF THE CHOICE SHOULD BE RENDERED*************************************************************************************


            for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(gRenderer, GAME_PAGE_2_WORDS[i], TAN, dimensions.w() / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;
        case 60:
            break;
        default:
            break;
    }
    return true;
}


#endif