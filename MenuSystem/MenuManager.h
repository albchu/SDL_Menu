#ifndef _MENU_MANAGER_H_
#define _MENU_MANAGER_H_

#include <map>

#include "SDL_Texture_Wrapper.h"
#include "Menu.h"


using namespace std;

class MenuManager
{
public:
	MenuManager(SDL_Renderer* new_renderer, int new_view_x, int new_view_y, int new_width, int new_height);
	void down();
	void up();
	void select();	// Selects the current highlighted option in the current displayed menu and does the required task
	Menu* createMenu(const char * title);
	void render();
	MenuOption* setupOption(Menu* menu, const char * option_id, const char * option_text, bool& flag);
	MenuOption* setupRangeOption(Menu* menu, const char * option_id, vector<const char *> pickbox, int& selectedIndex);
	MenuOption* setupOption(Menu* menu, const char * option_id, const char * option_text, Menu* next_menu, bool dontCreateBackButton = false);
	MenuOption* option_exists(Menu* menu, const char * option_id);
	MenuOption* option_exists(Menu* menu, vector<const char *> pickbox);
	void set_current_menu(const char * title, bool dontCreateBackButton = true);
	void set_current_menu(Menu * menu, bool dontCreateBackButton = true);
	MenuOption* get_option(Menu* menu, const char * option_id, const char * option_text);
	MenuOption* get_option(Menu* menu, const char * option_id, vector<const char *> pickbox);
private:
	SDL_Renderer* renderer;
	map<const char*, Menu*> menus;
	//map<const char*, map<const char *, MenuOptionData>> menuOptionDataMap;	// Maps options to their respective datas
	Menu* curr_menu;
	//Menu* prev_menu;
	int view_x;
	int view_y;
	int width;
	int height;
	const char * backText;
};

#endif