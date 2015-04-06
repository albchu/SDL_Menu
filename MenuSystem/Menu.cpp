#include "Menu.h"

//TODO: Optimize: can pass in the font for the title texture
Menu::Menu(SDL_Renderer* new_renderer, const char * new_title)
{
	selected_index = -1;
	title = new_title;
	renderer = new_renderer;
	titleTexture = new SDL_Texture_Wrapper(renderer);
	titleFontSize = 35;

	TTF_Font* titleFont = TTF_OpenFont( "../data/Fonts/Atmosphere-Regular.ttf", titleFontSize );
	SDL_Color textColor = { 0, 0, 0 };
	if( !titleTexture->loadFromRenderedText( title, textColor, titleFont ) )
	{
		printf( "Failed to render title texture!\n" );
	}

}

Menu::~Menu()
{
	titleTexture->free();
	for(MenuOption* option: options)
		delete option;
	options.clear();
	options.shrink_to_fit();
}

void Menu::render(int view_x, int view_y, int width, int height)
{
	int x = view_x + width/2;
	int y = view_y + height/4;
	int spacing_y = 5;

	titleTexture->render(x - titleTexture->getWidth()/2,y - titleFontSize * 2);

	for(int i = 0; i < options.size(); i++)
	{
		MenuOption* option = options[i];
		if(selected_index == i)
			option->setSelected(true);
		option->render(x - option->getButtonRect()->w/2, y - option->getButtonRect()->h/2);
		y += option->getButtonRect()->h + spacing_y;
	}
}

// Set the index for the selected option
void Menu::set_selected(int selected)
{
	if(selected < options.size() && selected >= 0)	// Size check
		selected_index = selected;
	else
		selected_index = 0;	// Else default it to zero. Can be problematic if nothing is set in the menu
}

void Menu::add_option(const char* option_name)
{
	MenuOption* option = new MenuOption(renderer, option_name);
	options.push_back(option);
}
