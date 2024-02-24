#ifdef PAGE_H

Page::Page(const int newPgNum, const int newTxtNum, const string* newWords, LTexture* newTextures){
    pgNum = newPgNum;
    txtNum = newTxtNum;
    pgWords = new string[txtNum];
    for (int i = 0; i < txtNum; i++)
        pgWords[i] = newWords[i];
    textures = newTextures;
}
Page::~Page(){
    delete[] pgWords;
    // delete[] textures;
}


void Page::mainMenuRenderer(SDL_DisplayMode dimensions, SDL_Renderer* renderer){
    for (int i = 0; i < txtNum; i++){
        textures[i].render((dimensions.w * (i + .5) / txtNum + 1) - textures[i].getWidth() / 2, ( dimensions.h - textures[i].getHeight() ) / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

// void taskBarRenderer(){
// for (int i = 0; i < TASKBAR_TEXTURES; i++)
//     TASKBAR[i].render((dimensions.w * (1 + i) / 3) - (TASKBAR[i].getWidth() / 2), (TASKBAR[i].getHeight() / 2), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
// }

// void tutorialRenderer(){
//     for (int i = 0; i < TUTORIAL_TEXTURES; i++){
//         if (i == 0)
//             textures[i].render((dimensions.w / 2) - textures[i].getWidth() / 2, (dimensions.h / 8) - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
//         else if (i % 2 == 1)
//             textures[i].render((dimensions.w / 2) - textures[i].getWidth() / 2, (dimensions.h / 8) + totalHeight(i) + 10 * i , NULL, 0, NULL, SDL_FLIP_NONE, renderer);
//         else
//             textures[i].render((dimensions.w / 2) - textures[i].getWidth() / 2, (dimensions.h / 8) + totalHeight(i) + 10 * i, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
//     }
// }

// void quotationPageRenderer(){
//     textures[0].render(dimensions.w / 2 - textures[0].getWidth() / 2, dimensions.h / 3 - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
//         for (int i = 1; i < QUOTATION_PAGE_TEXTURES; i++){
//             textures[i].render(dimensions.w / 2 - textures[i].getWidth() / 2, dimensions.h / 2 - textures[i].getHeight() + totalHeight(i) + 20, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
//         }
// }

// void choicePageRenderer(){
//     for (int i = 0; i < CHOICE_PAGE_TEXTURES; i++)
//         textures[i].render(dimensions.w / 2 - textures[i].getWidth() / 2, dimensions.h / 2 - textures[i].getHeight() + totalHeight(i) + (i*20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
// }

// void playerBarRenderer(){
//     for (int i = 0; i < PLAYER_TEXTURES; i++)
//         PLAYER_STATS[i].render((dimensions.w * (1 + i) / 4 - PLAYER_STATS[i].getWidth() / 2), dimensions.h / 8 - PLAYER_STATS[i].getHeight() * 4, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
// }

// void postChoicePageRenderer(){
//     textures[0].render(dimensions.w / 2 - textures[0].getWidth() / 2, dimensions.h / 3 - textures[0].getHeight() / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
//     for (int i = 1; i < POST_CHOICE_PAGE_TEXTURES; i++){
//         textures[i].render(dimensions.w / 2 - textures[i].getWidth() / 2, dimensions.h / 2 - textures[i].getHeight() + totalHeight(i) + (i * 20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
//     }
// }

// void textPageRenderer(){
//     for (int i = 0; i < TEXT_PAGE_TEXTURES; i++)
//         textures[i].render(dimensions.w / 2 - textures[i].getWidth() / 2, dimensions.h / 2 - textures[i].getHeight() + totalHeight(i) + (i * 20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
// }







int Page::getPgNum(){}
void Page::setPgNum(int newPgNum){}

int Page::getTxtNum(){}
void Page::setTxtNum(int newTxtNum){}

string* Page::getPgWords(){}
void Page::setPgWords(string* newWords){}

LTexture* Page::getTextures(){}
void Page::setTextures(LTexture* newTexture){}

#endif