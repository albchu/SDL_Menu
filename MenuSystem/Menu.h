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
	void add_option(const char* option);
	void set_selected(int selected);
	const char * get_title();
	vector<const char*> get_option_titles();

private:
	vector<MenuOption*> options;
	vector<const char*> optionTitles;
	SDL_Renderer* renderer;
	int selected_index;
	const char * title;
	SDL_Texture_Wrapper* titleTexture;
	int titleFontSize;
};

#endif