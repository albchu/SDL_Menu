#ifndef _MENU_OPTION_H_
#define _MENU_OPTION_H_

#include "SDL_Texture_Wrapper.h"

using namespace std;

// An option for the menu
class MenuOption
{
public:
	MenuOption(SDL_Renderer* new_renderer, const char* new_text, int new_font_size=20, const char* font_path="../data/Fonts/5thagent.ttf");
	//MenuOption(SDL_Renderer* new_renderer, const char* new_text);
	//void init(SDL_Renderer* new_renderer, const char* new_text, const char* font_path);
	~MenuOption();
	void render(int x, int y);
	void setSelected(bool selected);

private:
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
};

#endif