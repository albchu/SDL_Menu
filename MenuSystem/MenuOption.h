#ifndef _MENU_OPTION_H_
#define _MENU_OPTION_H_

#include <iostream>

#include "SDL_Texture_Wrapper.h"

using namespace std;

enum OptionType
{
	REDIRECT,
	FLAG,
	RANGE
};

// An option for the menu
class MenuOption
{
public:
	MenuOption(SDL_Renderer* new_renderer, const char* init_id, const char* new_text="", int new_font_size=20, const char* font_path="../data/Fonts/Queen of Camelot Regular.ttf");
	//MenuOption(SDL_Renderer* new_renderer, const char* new_text);
	//void init(SDL_Renderer* new_renderer, const char* new_text, const char* font_path);
	MenuOption();
	~MenuOption();
	virtual void render(int x, int y);
	void setSelected(bool selected);
	virtual SDL_Rect* getButtonRect();
	SDL_Texture_Wrapper* get_text_texture();
	void set_button_texture(const char* texture_path);
	void set_button_selected_texture(const char* texture_path);
	const char* get_id();

	// Option Data accessor/mutators
	void set_option_data(const char* menu_name);
	void set_option_data(bool& new_flag);

	OptionType get_type();
	const char* get_redirect_menu();
	bool get_flag();
	void toggle_flag();
	const char* get_text();
	void set_text(const char* new_text);

protected:
	const char * id;	// different from text incase text changes, this wont be lost
	const char* text;
	SDL_Texture_Wrapper* buttonTexture;
	SDL_Texture_Wrapper* buttonTextureSelected;
	SDL_Texture_Wrapper* textTexture;
	TTF_Font *font;
	SDL_Renderer* renderer;
	int font_size;
	int padding_w_scalar;
	int padding_h_scalar;
	bool is_selected;

	// Option Data. These fields can vary in which ones are filled at any time
	OptionType type;
	const char* redirect_menu;	// Name of the menu to redirect to: cant directly refer to menu due to circular dependancy issue
	bool* flag;	// Needs to record a pointer to the reference of the original boolean so that we will change that original boolean when we need to.

	SDL_Rect* buttonRenderQuad;

};

#endif