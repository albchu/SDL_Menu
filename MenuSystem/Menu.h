#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <vector>

#include "MenuOption.h"

using namespace std;

class Menu
{
public:
	Menu(SDL_Renderer* new_renderer, const char * new_title = "");
	~Menu();
	void render(int view_x, int view_y, int width, int height);
	MenuOption* add_option(const char* option);
	void set_selected(int selected);
	const char * get_title();
	vector<const char*> get_option_titles();
	int get_selected_index();
	void set_prev_menu(Menu* new_menu);
	Menu* get_prev_menu();
	vector<MenuOption*> get_options();

private:
	vector<MenuOption*> options;
	vector<const char*> optionTitles;
	SDL_Renderer* renderer;
	int selected_index;
	const char * title;
	SDL_Texture_Wrapper* titleTexture;
	int titleFontSize;
	Menu* prev_menu;	// Pointer to previous menu instance if there is one
};

#endif