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
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

MenuManager* manager;

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
		switch (Event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			running = false;
			break;

		case SDLK_DOWN:
			manager->down();
			break;
			
		case SDLK_UP:
			manager->up();
			break;
						
		case SDLK_LEFT:
			manager->left();
			break;
						
		case SDLK_RIGHT:
			manager->right();
			break;
			
		case SDLK_RETURN:
			manager->select();
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

	MenuManager* managerLocal = new MenuManager(gRenderer, 0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Menu* mainMenu = managerLocal->createMenu("Main Menu");
	Menu* newGame = managerLocal->createMenu("New Game");
	Menu* settings = managerLocal->createMenu("Settings");
	Menu* exitGame = managerLocal->createMenu("Exit Game");
	Menu* developer = managerLocal->createMenu("Developer Options");

	bool gameActivated = false;

	//New game menu setup
	//managerLocal->setupOption(newGame, "Select Number of Players", mainMenu);	// UPDATE PLZ
	//managerLocal->setupOption(newGame, "Select Number of Bots", mainMenu);	// UPDATE PLZ
	managerLocal->setupOption(newGame, "devoptions", "Developer Options", developer);
	managerLocal->setupOption(newGame, "launch", "Launch Game", gameActivated);

	// Dev options setup
	bool godmode = false;
	MenuOption* godModeOption = managerLocal->setupOption(developer, "devoptions", "Godmode Off", godmode);

	//Main menu setup
	vector<const char*> pickbox;
	pickbox.push_back("Choice 1");
	pickbox.push_back("Choice 2");
	pickbox.push_back("Choice 3");
	int selectedIndex = 1;

	managerLocal->setupRangeOption(mainMenu, "Some Pickbox", pickbox, selectedIndex);
	managerLocal->setupOption(mainMenu, "newgame", "New Game", newGame);
	managerLocal->setupOption(mainMenu, "settings", "Settings", settings);
	managerLocal->setupOption(mainMenu, "exitgame", "Exit Game", exitGame);

	managerLocal->set_current_menu("Main Menu");

	manager = managerLocal;	// Stupid way to scope variable for debugging

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

		//if(gameActivated)
		//{
		//	cout << "Game Activated!" << endl;
		//}
		//else
		//	cout << "Game Deactvated!" << endl;

		if(godmode)
		{
			godModeOption->set_text("God Mode On!");
		}
		else
			godModeOption->set_text("God Mode Off!");
		//cout << "Index: " << selectedIndex << endl;
	}

	//Free resources and close SDL
	close();

	return 0;
}