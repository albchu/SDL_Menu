#include "Menu.h"

Menu::Menu()
{
	selected_index = -1;
}


void Menu::render(int view_x, int view_y, int width, int height)
{
	int x = view_x + width/2;
	int y = view_y + height/2;
	for(MenuOption* option : options)
		option->render(x, y);
}

// Set the index for the selected option
void Menu::set_selected(int selected)
{
	if(selected < options.size() && selected >= 0)	// Size check
		selected_index = selected;
	else
		selected_index = 0;	// Else default it to zero. Can be problematic if nothing is set in the menu
}

void Menu::add_option(string option)
{
	options.push_back(option);
}
