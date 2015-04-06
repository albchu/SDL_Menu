#include "Menu.h"

Menu::Menu()
{
	selected_index = 0;
}


void Menu::render()
{

}

void Menu::add_option(string option)
{
	options.push_back(option);
}
