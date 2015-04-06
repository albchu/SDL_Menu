#include "MenuManager.h"

MenuManager::MenuManager(SDL_Renderer* new_renderer, int new_view_x, int new_view_y, int new_width, int new_height)
{
	renderer = new_renderer;
	curr_menu = NULL;
	prev_menu = NULL;

	view_x = new_view_x;
	view_y = new_view_y;
	width = new_width;
	height = new_height;
	backText = "Back";

}

void MenuManager::down()
{

}

void MenuManager::up()
{

}

void MenuManager::select()
{

}

void MenuManager::render(const char * title)
{
	curr_menu->render(view_x, view_y, width, height);
}

// Sets the current menu to be rendered by render()
void MenuManager::set_current_menu(const char * title)
{
	if(prev_menu != NULL)
		setupOption(curr_menu, backText, prev_menu);		// Set up the back button reference to the previous menu
		
	// Update previous menu
	prev_menu = curr_menu;
	curr_menu = menus[title];

	curr_menu->set_selected(0);		// Set the selected index to the top of the menu
}

// Returns whether the specified option exists or not in the current menu
bool MenuManager::option_exists(Menu* menu, const char * option)
{
	for(const char * option_name : menu->get_option_titles())
	{
		if(option_name == option)
			return true;
	}
	return false;
}


// Adds an option to the passed in menu and tracks the boolean attached to this option if it is selected
void MenuManager::setupOption(Menu* menu, const char * option, bool * flag)
{
	//If the option doesnt exist, create it in the menu
	if(!option_exists(menu, option))
		menu->add_option(option);

	map<const char *, MenuOptionData> optionDataMap;
	MenuOptionData optionData;
	optionData.type = FLAG;
	optionData.flag = flag;

	optionDataMap[option] = optionData;
	menuOptionDataMap[menu->get_title()] = optionDataMap;
}

// Adds an option to the passed in menu and tracks the title of the next menu attached to this option
void MenuManager::setupOption(Menu* menu, const char * option, Menu* next_menu)
{
	//If the option doesnt exist, create it in the menu
	if(!option_exists(menu, option))
		menu->add_option(option);

	map<const char *, MenuOptionData> optionDataMap;
	MenuOptionData optionData;
	optionData.type = REDIRECT;
	optionData.redirect = next_menu;

	optionDataMap[option] = optionData;
	menuOptionDataMap[menu->get_title()] = optionDataMap;
}

//// Adds a back button to the menu. Dont set up the return reference yet, since we need to know when its used for that info.
//void MenuManager::finalize(Menu* menu)
//{
//	menu->add_option(backText);
//}

Menu* MenuManager::createMenu(const char * title)
{
	Menu* menu = new Menu(renderer, title);
	menus[title] = menu;
	return menu;
}
