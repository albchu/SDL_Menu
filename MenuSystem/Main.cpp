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

SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool running = true;

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
			}
		}
	}

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void OnEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
	case SDL_QUIT:
		running = false;
		break;

	case SDL_KEYDOWN:
		//overMind->notify(Event->key.keysym.sym);

		switch (Event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			running = false;
			break;
		}
	}
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}

	//Event handler
	SDL_Event e;

	SDL_Color textColor1 = { 0, 0, 0 };
	SDL_Color textColor2 = { 0.5, 10, 0 };

	MenuManager* manager = new MenuManager(gRenderer, 0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Menu* menu = manager->createMenu("Main Menu");
	bool flag1 = true;
	manager->setupOption(menu, "Option1", &flag1);
	manager->setupOption(menu, "Option3", &flag1);
	manager->setupOption(menu, "Option2", &flag1);
	manager->set_current_menu("Main Menu");

	//While application is running
	while( running )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			OnEvent(&e);
		}

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		manager->render();

		//Update screen
		SDL_RenderPresent( gRenderer );
	}

	//Free resources and close SDL
	close();

	return 0;
}