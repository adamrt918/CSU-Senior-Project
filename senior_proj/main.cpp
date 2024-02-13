//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <../ltexture.hpp>
//#include <../lbutton.hpp>
#include <vector>

using namespace std;

//Background color black {r, g, b}
const SDL_Color BACKGROUND_COLOR = {0, 0, 0};

//Text color white {r, g, b}
const SDL_Color TEXT_COLOR = {255, 255, 255};

//Monitor data
SDL_DisplayMode dimensions;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Renderer
SDL_Renderer* renderer;

//Mouse button sprites and text texture
const int TEMP_PLACEHOLDER = 4;
int totalWordWidth;
string words[4] = {"Begin", "Tutorial", "Survey", "Exit"};
LTexture gTextTexture;
//LButton gButtons[TEMP_PLACEHOLDER];
LTexture gButtonSpriteSheetTexture;
SDL_Rect gSpriteClips[TEMP_PLACEHOLDER];


vector <SDL_Rect> wordBox;
LTexture textures[4];


//The page number that is being rendered to the texture.
int pgNum = 0;
int currentPg = 0;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

int calcXSpacing(int word, int i);

//Frees media and shuts down SDL
void close();



int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
		printf( "Failed to initialize!\n" );
    //Initial media load
    if( !loadMedia() )
        printf( "Failed to load media!\n" );
    //Main loop flag
    bool gaming = true;

    //Event handler
    SDL_Event e;
    
    //While application is running
    while( gaming )
    {
        //Load media only when the page is different
        if (currentPg != pgNum)
            if( !loadMedia() )
                printf( "Failed to load media!\n" );

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                gaming = false;
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor( renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255 );
        SDL_RenderClear( renderer );

        //Render current frame
        for (int i = 0; i < TEMP_PLACEHOLDER; i++){
            textures[i].render( calcXSpacing(textures[i].getWidth(), i), ( dimensions.h - textures[i].getHeight() ) / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
                // cout << "monitor width: " << dimensions.w << endl;
                // cout << "Slot: " << i << endl;
                // cout << "Word width: " << textures[i].getWidth() << endl;
        }

        //Update screen
        SDL_RenderPresent( renderer);
    }
	
	//Free resources and close SDL
	close();
	return 0;
}


bool init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
        return false;
    }

    //Get monitor dimensions
    if (SDL_GetCurrentDisplayMode(0, &dimensions) != 0)
    {
        printf("Unable to get display mode: %s", SDL_GetError());
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow( "A Solemn Evolution", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensions.w, dimensions.h, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Initialize renderer color to black
    SDL_SetRenderDrawColor( renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255 );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
	return true;
}

bool loadMedia()
{
	//Open the font
        //Need to put a variable for font size depending on the page
    
	// gTextTexture.gFont = TTF_OpenFont( "resources/Abadi_MT_Std.ttf", 72 );
	// if( gTextTexture.gFont == NULL )
	// {
	// 	printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
	// 	return false;
	// }

    for (int i = 0; i < TEMP_PLACEHOLDER; i++){
        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", 72);
        if (textures[i].gFont == NULL)
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		    return false;
        }
        
        
    }

    //Render text, determines the page that is loaded.
        //I need to create a function to format and change text sizes based on
        //what I want to display
        //
        //The following function can size text
        //SDL_TTF.SizeText(game.font, text_cstring, &text.rect.w, &text.rect.h)

    // if (!gTextTexture.loadFromRenderedText(renderer, "Begin    Survey    Tutorial    Exit", TEXT_COLOR))
    // {
    //     printf( "Failed to render text texture!\n" );
    //     return false;
    // }  
    for (int i = 0; i < TEMP_PLACEHOLDER; i++){
        if (!textures[i].loadFromRenderedText(renderer, words[i], TEXT_COLOR))
        {
            printf( "Failed to render text texture!\n" );
            return false;
        }
        totalWordWidth += textures[i].getWidth();
    }

	return true;
}


int calcXSpacing(int word, int i){
    int remainingWidth = dimensions.w - totalWordWidth;
    int spacing = dimensions.w / (TEMP_PLACEHOLDER + 1);
    spacing *= i + 1;
    return spacing;
}

void close()
{
	//Free loaded images
	gTextTexture.free();

	//Free global font
	TTF_CloseFont( gTextTexture.gFont );
	gTextTexture.gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


