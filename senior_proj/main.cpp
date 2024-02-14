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
const int TUTORIAL_PAGE = 2;

//Textures Per Page
const int START_PAGE_TEXTURES = 1;
const int MAIN_MENU_TEXTURES = 4; // 1 texture for each clickable word
const int TUTORIAL_TEXTURES = 12; // textures for individual highlights and going back to the main menu

//Words Per Page
const string TASKBAR_WORDS[2]{"Main Menu", "Exit to Desktop"};
const string MAIN_MENU_WORDS[MAIN_MENU_TEXTURES] = {"Begin", "Tutorial", "Survey", "Exit"};
const string TUTORIAL_WORDS[TUTORIAL_TEXTURES] = {"Tutorial", 
    "    The novel will measure three metrics throughout the chapter, health and sanity which affect the individual player, and reputation, which affects the games ending. The metrics are affected through user-made decisions. The page of the visual novel is turned by clicking the interactive text. The novel is only advanced when a decision is made or when the timer runs out. Once the game ends, the player can choose to return to the main menu or exit the game. Progress is not saved, but the game should only take about 20 minutes to complete. Once complete, please fill out the survey.",  
    "Health", 
    "    Losing all your health during a chapter will result in losing the ability to make the most heroic decision for the rest of the chapter, but restoring your health. Health restores at the beginning of a new chapter. Heroic decisions affect your health the most but have the least impact on your sanity.", 
    "Sanity", 
    "    Losing all of your sanity in a chapter will immediately train track your actions and prevent player choice, forcing the player to make cowardly decisions which impact reputation. Choices which are cowardly affect sanity the most but save your health. A new chapter will result in a restoration of sanity.", 
    "Reputation",
    "    Reputation will continue with you throughout the novel and will determine your game ending. To achieve the most favorable outcome, you must be willing to take risks and decide heroically. However, if you always choose the most heroic outcome, there is a chance that you will die. To make it to the end without dying, you must make decisions which are less heroic.",
    "Ending", 
    "    There are 3 endings. Play the game as a hero, as a human, or as a coward to see each ending." ,
    "Decisions",
    "    At various points throughout the novel, the player will need to make decisions by clicking on them with their mouse. It is not always clear what the right choice is in these decisions, as it is not always clear in life what decisions one should make. Often, decisions which are competent and correct in one situation are deluded and ineffective in another. Sometimes, there is no correct decision. Other times, decisions need to be made quickly. The decisions in this game are no different. It is meant to display the futility of choice in certain situations and the need for a higher power. Decisions affect health and/or sanity, and reputation."
};

//Background color black {r, g, b, alpha}
const SDL_Color BACKGROUND_COLOR = {0, 0, 0, SDL_ALPHA_OPAQUE};
const SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
const SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};

//Text sizes
const int HEADING_1 = 72;
const int HEADING_2 = 48;
const int HEADING_3 = 36;
const int WRITING = 24;

//Text color white {r, g, b}
SDL_Color textColor = {255, 255, 255, SDL_ALPHA_OPAQUE};

//Monitor data
SDL_DisplayMode dimensions;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Renderer
SDL_Renderer* renderer;

//Mouse button sprites and textures
const int MAX_TEXTURES = 20;
int totalWordWidth;
LTexture textures[MAX_TEXTURES];
LTexture MENU_BAR[2];

//The current page variable so the game knows what to load.
int currentPage = -1;
int newPage = 1;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Calculates what the X spacing should be between words that are rendered.
int calcXSpacing(int word, int i, int tNum);

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
                                            newPage = TUTORIAL_PAGE;
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
        /*Begin switch for which frames to Render*/
        switch (currentPage)
        {
            case MAIN_MENU_PAGE:
                for (int i = 0; i < MAIN_MENU_TEXTURES; i++)
                    textures[i].render(calcXSpacing(textures[i].getWidth(), i, MAIN_MENU_TEXTURES), ( dimensions.h - textures[i].getHeight() ) / 2, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
                break;
            case TUTORIAL_PAGE:
                int height = 0;
                for (int i = 0; i < TUTORIAL_TEXTURES; i++){
                    if (i == 0)
                        textures[i].render((dimensions.w / 2) - textures[i].getWidth() / 2, (dimensions.h / 8) + height, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
                    else if (i % 2 == 1)
                        textures[i].render((dimensions.w / 2) - textures[i].getWidth() / 2, (dimensions.h / 8) + height + 10 * i, NULL, 0, NULL, SDL_FLIP_NONE, renderer);
                    else
                        textures[i].render((dimensions.w / 2) - textures[i].getWidth() / 2, (dimensions.h / 8) + height + 10 * i, NULL, 0, NULL, SDL_FLIP_NONE, renderer);

                    height += textures[i].getHeight();
                }
                break;
        }
        

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
            for (int i = 0; i < MAIN_MENU_TEXTURES; i++){
                //Open the font
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
        case TUTORIAL_PAGE:
            for (int i = 0; i < TUTORIAL_TEXTURES; i++){
                //Open the font
                if (i == 0)
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_1);
                else if (i % 2 == 1)
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                else if (i % 2 == 0)
                    textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", HEADING_3);
                if (textures[i].gFont == NULL)
                {
                    printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                    return false;
                }
                //Load in the textures for rendering
                if (!textures[i].loadFromRenderedText(renderer, TUTORIAL_WORDS[i], textColor, dimensions.w / 1.3))
                {
                    printf( "Failed to render text texture!\n" );
                    return false;
                }
            }
            break;  
        
        
    }

	return true;
}

int calcXSpacing(int word, int i, int tNum){
    int remainingWidth = dimensions.w - totalWordWidth;
    int spacing = dimensions.w / (tNum + 1);
    spacing *= (i + 1);
    return spacing;
}

void close()
{
	//Free loaded textures, images, and font
    for (int i = 0; i < 10; i++){
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


