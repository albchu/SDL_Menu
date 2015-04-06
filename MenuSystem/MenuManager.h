#ifndef _MENU_MANAGER_H_
#define _MENU_MANAGER_H_

#include <map>

#include "SDL_Texture_Wrapper.h"
#include "Menu.h"

using namespace std;

class MenuManager
{
public:
	MenuManager(SDL_Renderer* new_renderer);
	void down();
	void up();
	void select();	// Selects the current highlighted option in the current displayed menu and does the required task
	void createMenu(const char * title);


private:
	SDL_Renderer* renderer;
	map<const char*, Menu> menus;
};

#endif