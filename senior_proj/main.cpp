#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include <../ltexture.hpp>

using namespace std;

// White color (R, G, B)
const SDL_Color TEXT_COLOR = {255, 255, 255};

// Black color (R, G, B)
const SDL_Color BACKGROUND_COLOR = {0, 0, 0};

//Global variable to hold display size
SDL_DisplayMode dm;

//Loads individual image
//SDL_Surface* loadSurface(string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

//Rendered texture
LTexture gTextTexture = LTexture();

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
//SDL_Surface* loadSurface(string path);

int main(int argc, char *argv[])
{
    //Game loop flag
    bool gaming = true;

    //Variables for TTF Rendering
    SDL_Rect* clip;
    double angle;
    SDL_Point* center;
    SDL_RendererFlip flip;

    SDL_Init(SDL_INIT_EVERYTHING);
    if (init() == false)
        printf("Failed to initialize!\n");

    if(!loadMedia())
			printf("Failed to load media!\n");

    SDL_Event windowEvent;

    while (gaming)
    {
        if ( SDL_PollEvent(&windowEvent))
            if (SDL_QUIT == windowEvent.type)
                gaming = false;

        //Clear Screen
        SDL_SetRenderDrawColor( gTextTexture.gRenderer, TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b, 255 );
        SDL_RenderClear( gTextTexture.gRenderer );

        //Render current frame
        gTextTexture.render( ( dm.w - gTextTexture.getWidth() ) / 2, ( dm.h - gTextTexture.getHeight() ) / 2, clip, angle, center, flip );

        //Update screen
        //cout << gTextTexture.gRenderer << endl;
        SDL_RenderPresent( gTextTexture.gRenderer );
        

        // //Apply the PNG image
        //SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
    
        // //Update the surface
        // SDL_UpdateWindowSurface(gWindow);
    }

    close();

    return EXIT_SUCCESS;
}



bool init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
    
    // Get the user's primary display size
    if (SDL_GetCurrentDisplayMode(0, &dm) != 0) 
    {
        SDL_Log("Unable to get display mode: %s", SDL_GetError());
        return false;
    }
    
    // Create an SDL window in fullscreen
    gWindow = SDL_CreateWindow("Full Size Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h - 50, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) 
    {
        SDL_Log("Unable to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // //Initialize SDL_image
    // int imgFlags = IMG_INIT_PNG;
    // if( !( IMG_Init( imgFlags ) & imgFlags ) )
    // {
    //     printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    //     return false;
    // }

    // //Get window surface
    // gScreenSurface = SDL_GetWindowSurface(gWindow);
    // if (gScreenSurface == NULL)
    // {
    //     printf( "Screen Surface is still NULL.\n");
    //     return false;
    // }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }

    //Create vsynced renderer for window
    gTextTexture.gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gTextTexture.gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Initialize background color to black
    SDL_SetRenderDrawColor( gTextTexture.gRenderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255 );

	return true;
}

bool loadMedia()
{
    /*PNG LOADING -- CURRENTLY UNNEEDED*/
	// //Load PNG surface
	// gPNGSurface = loadSurface( "loaded.png" );
	// if( gPNGSurface == NULL )
	// {
	// 	printf( "Failed to load PNG image!\n" );
	// 	return false;
	// }

    //Load the font
    gTextTexture.gFont = TTF_OpenFont( "lazy.ttf", 28 );
    if(gTextTexture.gFont == NULL)
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }

    //Render text
    if( !gTextTexture.loadFromRenderedText( "The quick brown fox jumps over the lazy dog", TEXT_COLOR ) )
    {
        printf( "Failed to render text texture!\n" );
        return false;
    }
    
	return true;
}

/*
//SDL_Surface* loadSurface(string path)
{
    PNG LOADING -- CURRENTLY UNNEEDED
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

    
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return NULL;
    }
    
    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if( optimizedSurface == NULL )
    {
        printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        return NULL;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

	return optimizedSurface;
    
   return 0;
}
*/


void close()
{
	//Free loaded image
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

    //Free global font
    TTF_CloseFont( gTextTexture.gFont );
    gTextTexture.gFont = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gTextTexture.gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gTextTexture.gRenderer = NULL;

	//Quit SDL subsystems
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
