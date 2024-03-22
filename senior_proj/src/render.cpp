#ifdef RENDER_H

Render::Render(LTexture* textures, Window* window)
{
    this->textures = textures;
    dms = window;
}

Render::~Render()
{
}

void Render::startPageRenderer(SDL_Renderer* renderer){

    //factor for scaling the image to fit screen width
    int x = dms->w() / 2 - textures[1].getWidth() / 2;
    int y = dms->h() / 4 * 3 - textures[1].getHeight() / 2;

    //Render
    textures[0].render(dms->w() / 2 - textures[0].getWidth() / 2, dms->h() / 2 - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    textures[1].render(x, y, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void Render::muteButtonRenderer(bool unMute, SDL_Renderer* renderer, SDL_Rect* MUTE_BUTTON_SPRITES, LTexture* MUTE_BUTTON){
    MUTE_BUTTON->render(0,0, &MUTE_BUTTON_SPRITES[unMute], 0, NULL, SDL_FLIP_NONE, renderer);
}

void Render::timerRenderer(SDL_Renderer* renderer, SDL_Rect* timerSprites, LTexture* timerTexture, int seconds){
    if (seconds < 11 && seconds >= 0)
        timerTexture->render(dms->w() - timerSprites[seconds].w, 0, &timerSprites[seconds], 0, NULL, SDL_FLIP_NONE, renderer);
}


void Render::mainMenuRenderer(SDL_Renderer* renderer){
    for (int i = 0; i < MAIN_MENU_TEXTURES; i++){
        //Formulas for text position based on texture dimensions and screen dimensions
        int x = (dms->w() * (i + 1) / (MAIN_MENU_TEXTURES + 1 )) - textures[i].getWidth() / 2;
        int y = dms->h() / 2 - textures[i].getHeight() / 2;

        //Validation to keep text on screen
        x = validateX(x, textures[i].getWidth());
        y = validateY(y, textures[i].getHeight());

        //Render
        textures[i].render(x, y, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void Render::tutorialRenderer(SDL_Renderer* renderer){
    for (int i = 0; i < TUTORIAL_TEXTURES; i++){
        if (i == 0)
            textures[i].render((dms->w() / 2) - textures[i].getWidth() / 2, (dms->h() / 8) - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        else if (i % 2 == 1)
            textures[i].render((dms->w() / 2) - textures[i].getWidth() / 2, (dms->h() / 8) + totalHeight(i) + 10 * i , NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        else
            textures[i].render((dms->w() / 2) - textures[i].getWidth() / 2, (dms->h() / 8) + totalHeight(i) + 10 * i, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void Render::taskBarRenderer(SDL_Renderer* renderer, LTexture* TASKBAR){
    for (int i = 0; i < TASKBAR_TEXTURES; i++){
        //Formulas for text position based on texture dimensions and screen dimensions
        int x = dms->w() * (1 + i) / 3 - TASKBAR[i].getWidth() / 2;
        int y = dms->h() / 64;

        //Validation to keep text on screen
        x = validateX(x, TASKBAR[i].getWidth());
        y = validateY(y, TASKBAR[i].getHeight());      

        //Render
        TASKBAR[i].render(x, y, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void Render::playerBarRenderer(SDL_Renderer* renderer, LTexture* PLAYER_STATS){

    for (int i = 0; i < PLAYER_TEXTURES; i++){
        //Formulas for text position based on texture dimensions and screen dimensions
        int x = dms->w() * (1 + i) / 4 - PLAYER_STATS[i].getWidth() / 2;
        int y = dms->h() / 16 - PLAYER_STATS[i].getHeight() / 2;

        //Validation to keep text on screen
        x = validateX(x, PLAYER_STATS[i].getWidth());
        y = validateY(y, PLAYER_STATS[i].getHeight()); 

        //Render
        PLAYER_STATS[i].render(x, y, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void Render::quotationPageRenderer(SDL_Renderer* renderer){
    textures[0].render(dms->w() / 2 - textures[0].getWidth() / 2, dms->h() / 3 - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        for (int i = 1; i < QUOTATION_PAGE_TEXTURES; i++)
            textures[i].render(dms->w() / 2 - textures[i].getWidth() / 2, dms->h() / 2 - textures[i].getHeight() + totalHeight(i) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void Render::choicePageRenderer(SDL_Renderer* renderer, Player* gamer, bool isOut)
{
    if (!gamer->checkInsanity() && !isOut)
        for (int i = 0; i < CHOICE_PAGE_TEXTURES; i++){
            //Formulas for text position based on texture dimensions and screen dimensions
            int x = dms->w() / 2 - textures[i].getWidth() / 2;
            int y = dms->h() / 2 - totalHeight(4) / 2 + totalHeight(i) + (i * 20);

            //Validation to keep text on screen
            x = validateX(x, textures[i].getWidth());
            y = validateY(y, textures[i].getHeight()); 

            //Render    
            textures[i].render(x, y, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        }
    else{
        textures[0].render(dms->w() / 2 - textures[0].getWidth() / 2, dms->h() / 2 - textures[0].getHeight() + totalHeight(0), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        textures[1].render(dms->w() / 2 - textures[1].getWidth() / 2, dms->h() / 2 - textures[1].getHeight() + totalHeight(1) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void Render::postChoicePageRenderer(SDL_Renderer* renderer){
    textures[0].render(dms->w() / 2 - textures[0].getWidth() / 2, dms->h() / 3 - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
        textures[i].render(dms->w() / 2 - textures[i].getWidth() / 2, dms->h() / 2 - textures[i].getHeight() + totalHeight(i) + (i * 20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void Render::textPageRenderer(SDL_Renderer* renderer){
    for (int i = 0; i < TEXT_PAGE_TEXTURES; i++){
        //Formulas for text position based on texture dimensions and screen dimensions
        int x = dms->w() / 2 - textures[i].getWidth() / 2;
        int y = dms->h() / 2 - textures[i].getHeight() / 2 + totalHeight(i) + (i * 20);

        //Validation to keep text on screen
        x = validateX(x, textures[i].getWidth());
        y = validateY(y, textures[i].getHeight()); 

        //Render
        textures[i].render(x, y, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

void Render::outcomePageRenderer(SDL_Renderer* renderer){
    textures[0].render(dms->w() / 2 - textures[0].getWidth() / 15, dms->h() / 2 - textures[0].getHeight() / 2 + totalHeight(0), NULL, 0, NULL, SDL_FLIP_NONE, renderer);    
    textures[1].render(dms->w() / 2 - textures[1].getWidth() / 2, dms->h() / 2 - textures[1].getHeight() / 2 + totalHeight(1) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

void Render::versePageRenderer(SDL_Renderer* renderer){
    for (int i = 0; i < VERSE_PAGE_TEXTURES; i++)
        textures[i].render(dms->w() / 2 - textures[i].getWidth() / 2, dms->h() / 2 - textures[i].getHeight() + totalHeight(i) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
}

int Render::totalHeight(int tNum){
    int height = 0;
    for (int i = 0; i < tNum; i++)
        height += textures[i].getHeight();
    return height;
}

int Render::validateX(int xx, int textureWidth){
    int x = xx;
    if (x > (dms->w() - textureWidth))
        x = dms->w() - textureWidth;
    return x;
}

int Render::validateY(int yy, int textureHeight){
    int y = yy;
    if (y > (dms->h() - textureHeight))
        y = dms->h() - textureHeight;
    return y;
}

#endif
