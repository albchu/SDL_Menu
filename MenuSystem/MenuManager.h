#ifndef _MENU_MANAGER_H_
#define _MENU_MANAGER_H_

#include <map>

#include "SDL_Texture_Wrapper.h"
#include "Menu.h"

enum MenuOptionType
{
	REDIRECT,
	FLAG
};

struct MenuOptionData
{
	MenuOptionType type;
	Menu* redirect;
	bool * flag;
};

using namespace std;

class MenuManager
{
public:
	MenuManager(SDL_Renderer* new_renderer, int new_view_x, int new_view_y, int new_width, int new_height);
	void down();
	void up();
	void select();	// Selects the current highlighted option in the current displayed menu and does the required task
	Menu* createMenu(const char * title);
	void render(const char * title);
	//void finalize(Menu* menu);
	void setupOption(Menu* menu, const char * option, bool * flag);
	void setupOption(Menu* menu, const char * option, Menu* next_menu);
	bool option_exists(Menu* menu, const char * option);

private:
	SDL_Renderer* renderer;
	map<const char*, Menu*> menus;
	map<const char*, map<const char *, MenuOptionData>> menuOptionDataMap;	// Maps options to their respective datas
	Menu* curr_menu;
	Menu* prev_menu;
	int view_x;
	int view_y;
	int width;
	int height;
	const char * backText;
};

#endif