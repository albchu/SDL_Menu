#include "MenuManager.h"

MenuManager::MenuManager(SDL_Renderer* new_renderer, int new_view_x, int new_view_y, int new_width, int new_height)
{
	renderer = new_renderer;
	curr_menu = NULL;
	//prev_menu = NULL;

	view_x = new_view_x;
	view_y = new_view_y;
	width = new_width;
	height = new_height;
	backText = "Back";

}

void MenuManager::down()
{
	int curr_selected = curr_menu->get_selected_index() + 1;
	curr_selected = (curr_selected) % curr_menu->get_option_ids().size();
	curr_menu->set_selected(curr_selected);
}

void MenuManager::up()
{
	int curr_selected = curr_menu->get_selected_index() - 1;
	// This is a c++ issue with negative modulo numbers: Workaround is to add the size to make it positive if the index goes negative
	if(curr_selected < 0)
		curr_selected = curr_selected + curr_menu->get_option_ids().size();
	curr_selected = (curr_selected) % curr_menu->get_option_ids().size();
	curr_menu->set_selected(curr_selected);
}

void MenuManager::select()
{
	MenuOption* option = curr_menu->get_options()[curr_menu->get_selected_index()];

	if(option->get_type() == REDIRECT)
	{
		// Update previous menu
		Menu* new_curr_menu = menus[option->get_redirect_menu()];
		//new_curr_menu->set_prev_menu(curr_menu);	
		set_current_menu(new_curr_menu, true);
	}
	else if(option->get_type() == FLAG)		// Toggle the boolean
	{
		//bool aflag = *option->get_flag();
		option->toggle_flag();
		//aflag = true;
	}

}

void MenuManager::render()
{
	curr_menu->render(view_x, view_y, width, height);
}

// Sets the current menu to be rendered by render()
void MenuManager::set_current_menu(const char * title, bool dontCreateBackButton)
{
	set_current_menu( menus[title], dontCreateBackButton);
}

void MenuManager::set_current_menu(Menu * menu, bool dontCreateBackButton)
{
	if(menu->get_prev_menu() != NULL)
		setupOption(menu, backText, backText, curr_menu, dontCreateBackButton);		// Set up the back button reference to the previous menu
	curr_menu = menu;
	curr_menu->set_selected(0);		// Set the selected index to the top of the menu
}

// Returns whether the specified option exists or not in the current menu
MenuOption* MenuManager::option_exists(Menu* menu, const char * option_id)
{
	for(MenuOption* option : menu->get_options())
	{
		if(option_id == option->get_text())
			return option;
	}
	return NULL;
}


// Adds an option to the passed in menu and tracks the boolean attached to this option if it is selected
MenuOption* MenuManager::setupOption(Menu* menu, const char * option_id, const char * option_text, bool& flag)
{
	//If the option doesnt exist, create it in the menu
	MenuOption* option = get_option(menu, option_id, option_text);

	option->set_option_data(flag);
	return option;
}

// Adds an option to the passed in menu and tracks the title of the next menu attached to this option
MenuOption* MenuManager::setupOption(Menu* menu, const char * option_id, const char * option_text, Menu* next_menu, bool dontCreateBackButton)
{
	MenuOption* option = get_option(menu, option_id, option_text);	//If the option doesnt exist, create it in the menu

	option->set_option_data(next_menu->get_title());

	if(!dontCreateBackButton)
	{
		// Set up the previous menu button tracking
		next_menu->set_prev_menu(menu);
		setupOption(next_menu, backText, backText, menu, true);
	}
	return option;
}

Menu* MenuManager::createMenu(const char * title)
{
	Menu* menu = new Menu(renderer, title);
	menus[title] = menu;
	return menu;
}

// If the option doesnt exist, this will create it and return the option object
MenuOption* MenuManager::get_option(Menu* menu, const char * option_id, const char * option_text)
{
	//If the option doesnt exist, create it in the menu
	MenuOption* option = option_exists(menu, option_id);
	if(option == NULL)
		return menu->add_option(option_id, option_text);	// Make the ID the name since none was given
	return option;
}

// If the option doesnt exist, this will create it and return the option object
MenuOption* MenuManager::get_option(Menu* menu, const char * option_id, vector<const char *> pickbox)
{
	//If the option doesnt exist, create it in the menu
	MenuOption* option = option_exists(menu, option_id);
	if(option == NULL)
		return menu->add_option(option_id, pickbox);	// Make the ID the name since none was given
	return option;
}

MenuOption* MenuManager::setupRangeOption(Menu* menu, const char * option_id, vector<const char *> pickbox, int& selectedIndex)
{
	MenuOption* option = get_option(menu, option_id, pickbox);	//If the option doesnt exist, create it in the menu

	return option;
}
