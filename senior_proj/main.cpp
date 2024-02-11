#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

//Loads individual image
SDL_Surface* loadSurface(string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

int main(int argc, char *argv[])
{
    //Game loop flag
    bool gaming = true;

    SDL_Init(SDL_INIT_EVERYTHING);
    if (init() == false)
        printf("Failed to initialize!\n");

    if(!loadMedia())
			printf("Failed to load media!\n");

    SDL_Event windowEvent;

    while (gaming)
    {
        if ( SDL_PollEvent( &windowEvent ) )
            if (SDL_QUIT == windowEvent.type )
                gaming = false;

        //Apply the PNG image
        SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );
    
        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
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
    SDL_DisplayMode dm;
    if (SDL_GetCurrentDisplayMode(0, &dm) != 0) 
    {
        SDL_Log("Unable to get display mode: %s", SDL_GetError());
        return false;
    }
    
    // Create an SDL window in fullscreen
    gWindow = SDL_CreateWindow("Full Size Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) 
    {
        SDL_Log("Unable to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    //Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    if (gScreenSurface == NULL)
    {
        printf( "Screen Surface is still NULL.\n");
        return false;
    }

	return true;
}

bool loadMedia()
{
	//Load PNG surface
	gPNGSurface = loadSurface( "loaded.png" );
	if( gPNGSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		return false;
	}
	return true;
}

SDL_Surface* loadSurface(string path)
{
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
}

void close()
{
	//Free loaded image
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
