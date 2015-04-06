#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <vector>

#include "MenuOption.h"

using namespace std;

class Menu
{
public:
	Menu(SDL_Renderer* new_renderer);
	~Menu();
	void render(int view_x, int view_y, int width, int height);
	void add_option(const char* option);
	void set_selected(int selected);

private:
	vector<MenuOption*> options;
	SDL_Renderer* renderer;
	int selected_index;
};

#endif