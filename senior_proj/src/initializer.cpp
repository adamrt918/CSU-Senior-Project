#ifdef INITIALIZER_H

Initializer::Initializer()
{

}

Initializer::~Initializer()
{

}

bool Initializer::init()
{
        // Get the user's primary display size
        SDL_DisplayMode dm;
        if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
        printf("Unable to get display mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    return true;

}

#endif