//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <../ltexture.hpp>
#include <vector>

/*Notes
    - The coordinates (0,0) in SDL is the top left of the screen, the y
      increases as the point moves down the screen, and decreases back to 0 if
      it moves up.
*/

using namespace std;

//Page Numbers
const int START_PAGE = 0;
const int MAIN_MENU_PAGE = 1;
const int TUTORIAL_PAGE = 1.1;

//Textures Per Page
const int START_PAGE_TEXTURES = 1;
const int MAIN_MENU_TEXTURES = 4; // 1 texture for each clickable word
const int TUTORIAL_TEXTURES = 2; // textures for individual highlights and going back to the main menu

//Words Per Page
const string MAIN_MENU_WORDS[4] = {"Begin", "Tutorial", "Survey", "Exit"};


//Background color black {r, g, b}
const SDL_Color BACKGROUND_COLOR = {0, 0, 0, SDL_ALPHA_OPAQUE};
const SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
const SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};

//Text color white {r, g, b}
SDL_Color textColor = {255, 255, 255, SDL_ALPHA_OPAQUE};

//Monitor data
SDL_DisplayMode dimensions;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Renderer
SDL_Renderer* renderer;

//Mouse button sprites and textures
const int TEMP_PLACEHOLDER = 4;
int totalWordWidth;
LTexture textures[10];

//The current page variable so the game knows what to load.
int currentPage = -1;
int newPage = 1;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Calculates what the X spacing should be between words that are rendered.
int calcXSpacing(int word, int i);

//Frees media and shuts down SDL
void close();



int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
		printf( "Failed to initialize!\n" );

    //Main loop flag
    bool gaming = true;

    //Event handler
    SDL_Event e;
    
    /*GAME LOOP*/
    while( gaming )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
                gaming = false;

            //Handle events based on the page
            /*START SWITCH STATEMENT FOR EVENTS BASED ON PAGE*/
            switch (currentPage)
            {
                case START_PAGE:
                    break;
                case MAIN_MENU_PAGE:                        
                    //Check if the mouse click is on a button
                    for (int i = 0; i < MAIN_MENU_TEXTURES; i++)
                    {
                        if (textures[i].isMouseOver(textures[i].getRect()))
                        {   textColor = RED;
                            textures[i].loadFromRenderedText(renderer, MAIN_MENU_WORDS[i], textColor);
                            {
                                if(e.type == SDL_MOUSEBUTTONDOWN)
                                {
                                    switch (i){
                                        case 0: 
                                            cout << "Going into main game loop" << endl;

                                            break;
                                        case 1:
                                            cout << "Display the tutorial" << endl;
                                            break;
                                        case 2: 
                                            cout << "Here is the survey link: " << endl;
                                            break;
                                        case 3:
                                            gaming = false;
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        else
                            textColor = WHITE;
                            textures[i].loadFromRenderedText(renderer, MAIN_MENU_WORDS[i], textColor);
                    }
                    break;
                /*END MAIN MENU Events*/

                default:
                    break;
                /*END EVENTS BASED ON PAGE SWITCH STATEMENT*/
            }
        }
        //Load new media whenever the page we are on does not match the new page we
        //are supposed to be on
        if (currentPage != newPage ) 
        {
            if( !loadMedia() ){
                cout << "Failed to load media on page " << newPage << "!\n";
                break;
            }
            //Once the media is loaded, the player is on the new page.
            currentPage = newPage;
        }

        //Clear screen
        SDL_SetRenderDrawColor( renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a );
        SDL_RenderClear( renderer );

        //Render current frame
        for (int i = 0; i < TEMP_PLACEHOLDER; i++)
            textures[i].render(calcXSpacing(textures[i].getWidth(), i), ( dimensions.h - textures[i].getHeight() ) / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);

        //Update screen
        SDL_RenderPresent( renderer);
    }
	/*END GAME LOOP*/
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
    //The following function can size text
    //SDL_TTF.SizeText(game.font, text_cstring, &text.rect.w, &text.rect.h)
    switch (newPage)
    {
        case START_PAGE:
            break;
        case MAIN_MENU_PAGE:
            //Open the font
            int textureNum = 4;
            for (int i = 0; i < textureNum; i++){
                textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", 72);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, MAIN_MENU_WORDS[i], textColor))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
                totalWordWidth += textures[i].getWidth();   
            }
            break;  
        
        
    }

	return true;
}

int calcXSpacing(int word, int i){
    int remainingWidth = dimensions.w - totalWordWidth;
    int spacing = dimensions.w / (TEMP_PLACEHOLDER + 1);
    spacing *= (i + 1);
    return spacing;
}

void close()
{
	//Free loaded textures, images, and font
    for (int i = 0; i < TEMP_PLACEHOLDER; i++){
        textures[i].free();
        TTF_CloseFont( textures[i].gFont );
    }

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


