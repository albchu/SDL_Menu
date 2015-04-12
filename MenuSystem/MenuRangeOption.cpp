#include "MenuRangeOption.h"

MenuRangeOption::MenuRangeOption(SDL_Renderer* new_renderer, const char* init_id, vector<const char*> new_pickbox, int& init_selected_index, int new_font_size, const char* font_path)
{
	type = RANGE;
	buttonRenderQuad = new SDL_Rect();
	description = new MenuOption(new_renderer, init_id, init_id, new_font_size, font_path);
	rightButton = new MenuOption(new_renderer, init_id, "      ", new_font_size, font_path);
	pickboxOption = new MenuOption(new_renderer, init_id, "PLACEHOLDER", new_font_size, font_path);
	pickBox = new_pickbox;
	selectedIndex = &init_selected_index;
	setPickboxIndex(init_selected_index);
	font_size = new_font_size;
	padding_w_scalar = 2;	// Higher the number, the larger the padding
	padding_h_scalar = 2;	// Higher the number, the larger the padding

	rightButton->set_button_texture("../data/images/Menu/glossy_button_range_rectangle.bmp");
	rightButton->set_button_selected_texture("../data/images/Menu/glossy_button_range_selected_rectangle.bmp");
	pickboxOption->set_button_texture("../data/images/Menu/pickbox.bmp");
}

//Required to render both buttons
void MenuRangeOption::render(int x, int y)
{
	SDL_Rect* descriptionRect = description->getButtonRect();
	SDL_Rect* pickBoxRect = pickboxOption->getButtonRect();
	SDL_Rect* rightRect = rightButton->getButtonRect();

	description->render(x,y);//, NULL, 0, rotate_center, SDL_FLIP_NONE);
	rightButton->setSelected(is_selected);
	rightButton->render(x + descriptionRect->w + pickBoxRect->w + padding_w_scalar + padding_w_scalar, y);//, NULL, 0, rotate_center, SDL_FLIP_NONE);

	pickboxOption->render(x + descriptionRect->w + padding_w_scalar, y);
}

// This should set the int passed into this range option
void MenuRangeOption::setPickboxIndex(int index)
{
	*selectedIndex = index;
	pickboxOption->set_text(pickBox[*selectedIndex]);

	getButtonRect();
}


SDL_Rect* MenuRangeOption::getButtonRect()
{
	SDL_Rect* descriptionRect = description->getButtonRect();
	SDL_Rect* pickBoxRect = pickboxOption->getButtonRect();
	SDL_Rect* rightRect = rightButton->getButtonRect();

	//Update rendering space and render to screen
	buttonRenderQuad->w = descriptionRect->w + pickBoxRect->w + rightRect->w;// + (font_size * padding_w_scalar);
	buttonRenderQuad->h = descriptionRect->h;// + pickboxOption->get_text_texture()->getHeight() + rightButton->get_text_texture()->getHeight() + (font_size * padding_h_scalar);

	return buttonRenderQuad;
}

int MenuRangeOption::getPickboxIndex()
{
	return *selectedIndex;
}

vector<const char*> MenuRangeOption::get_pickbox()
{
	return pickBox;
}

