/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings

#include "SDL_Texture_Wrapper.h"

#include <stdio.h>
#include <cmath>

#include "MenuOption.h"
#include "Menu.h"
#include "MenuManager.h"

#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
SDL_Texture_Wrapper* gTextTexture;

//Rendered texture background
SDL_Texture_Wrapper* gBGTexture;

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed image
SDL_Surface* gStretchedSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				//Get window surface for image rendering
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
		}
	}

	//Initialize SDL_Texture_Wrapper
	gTextTexture = new SDL_Texture_Wrapper(gRenderer);
	gBGTexture = new SDL_Texture_Wrapper(gRenderer);

	return success;
}


SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

void close()
{
	//Free loaded images
	gTextTexture->free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	SDL_Color textColor1 = { 0, 0, 0 };
	SDL_Color textColor2 = { 0.5, 10, 0 };

	//MenuOption* option = new MenuOption(gRenderer, "fuck you right in the dick hole");
	//Menu* menu = new Menu(gRenderer, "Menu Title");
	//menu->add_option("helloWorld");
	//menu->add_option("helloWorld2");
	//menu->add_option("helloWorld3");
	//menu->add_option("this is a longer string");
	//menu->set_selected(0);

	MenuManager* manager = new MenuManager(gRenderer, 0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Menu* menu = manager->createMenu("Main Menu");
	bool flag1 = true;
	manager->setupOption(menu, "Option1", &flag1);
	manager->setupOption(menu, "Option3", &flag1);
	manager->setupOption(menu, "Option2", &flag1);
	manager->set_current_menu("Main Menu");
	//manager->finalize(menu);

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		//menu->render(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);

		manager->render("Main Menu");

		//Update screen
		SDL_RenderPresent( gRenderer );
	}

	//Free resources and close SDL
	close();

	return 0;
}