#ifdef MAINMENU_h
#define MAINMENU_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <../ltexture.hpp>

class MainMenu
{
    public:

    //Constructor
    mainmenu();
    //Destructor
    ~mainmenu();
    
    //Loads the textures needed for the main menu
    bool mediaLoader();

    private:

    //Number of textures on the main menu
    const int NUMBER_OF_TEXTURES = 4;
}


#endif