#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <string>
#include <vector>

#include "MenuOption.h"

using namespace std;

class Menu
{
public:
	Menu();
	void render(int view_x, int view_y, int width, int height);
	void add_option(string option);
	void set_selected(int selected);

private:
	vector<MenuOption*> options;
	int selected_index;
};

#endif