#ifdef RENDER_H

Render::Render(LTexture* textures)
{
    this->textures = textures;
}

Render::~Render()
{
}

void Render::choicePageRenderer(int chooser, SDL_Renderer* renderer, Player* gamer)
{
    dimensions.initWindow();
    if (!gamer->getInsane())
        for (int i = 0; i < CHOICE_PAGE_TEXTURES; i++)
            textures[i].render(dimensions.w() / 2 - textures[i].getWidth() / 2, dimensions.h() / 2 - textures[i].getHeight() + totalHeight(i) + (i*20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    else{
        textures[0].render(dimensions.w() / 2 - textures[0].getWidth() / 2, dimensions.h() / 2 - textures[0].getHeight() + totalHeight(0) + (0*20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
        textures[1].render(dimensions.w() / 2 - textures[1].getWidth() / 2, dimensions.h() / 2 - textures[1].getHeight() + totalHeight(1) + (1*20), NULL, 0, NULL, SDL_FLIP_NONE, renderer);
    }
}

int Render::totalHeight(int tNum){
    int height = 0;
    for (int i = 0; i < tNum; i++)
        height += textures[i].getHeight();
    return height;
}

#endif
