#ifndef _MENU_RANGE_OPTION_H
#define _MENU_RANGE_OPTION_H

#include <vector>

#include "MenuOption.h"

using namespace std;

// A sub menu option that involves selecting through a list of options
class MenuRangeOption : public MenuOption	// Inheritance so i can use the same calls in menu
{
public:
	MenuRangeOption(SDL_Renderer* new_renderer, const char* init_id, vector<const char*> new_pickbox, int new_font_size=20, const char* font_path="../data/Fonts/Queen of Camelot Regular.ttf");
	virtual void render(int x, int y);
	void setPickboxIndex(int index);
	virtual SDL_Rect* getButtonRect();

private:
	//SDL_Renderer* renderer;
	vector<const char*> pickBox;	// List of options to be able to be picked 
	MenuOption* description;
	MenuOption* rightButton;
	MenuOption* pickboxOption;
	int padding_w_scalar;
	int padding_h_scalar;
	int selectedIndex;
};

#endif