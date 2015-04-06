#include "MenuOption.h"

//TODO: Enhancement: pass in textures for buttons rather than recreate them every goddamn time
MenuOption::MenuOption(SDL_Renderer* new_renderer, const char* new_text, int new_font_size, const char* font_path)
{
	text = new_text;
	renderer = new_renderer;
	font_size = new_font_size;
	padding_w_scalar = 2;	// Higher the number, the larger the padding
	padding_h_scalar = 2;	// Higher the number, the larger the padding
	is_selected = false;

	font = TTF_OpenFont( font_path, font_size );

	// Instantiate objects
	textTexture  = new SDL_Texture_Wrapper(renderer);
	buttonTexture  = new SDL_Texture_Wrapper(renderer);
	buttonTextureSelected  = new SDL_Texture_Wrapper(renderer);

	// Load text
	SDL_Color textColor = { 0, 0, 0 };
	if( !textTexture->loadFromRenderedText( text, textColor, font ) )
	{
		printf( "Failed to render text texture!\n" );
	}

	// Load background button
	if( !buttonTexture->loadFromFile("../data/images/Menu/glossy_button_blank_black_rectangle.bmp") )
	{
		printf( "Failed to render button texture!\n" );
	}

	// Load background selected button
	if( !buttonTextureSelected->loadFromFile("../data/images/Menu/glossy_button_blank_yellow_rectangle.bmp") )
	{
		printf( "Failed to render button texture!\n" );
	}

	buttonRenderQuad = new SDL_Rect();
	//Set rendering space and render to screen
	buttonRenderQuad->w = textTexture->getWidth() + (font_size * padding_w_scalar);
	buttonRenderQuad->h = textTexture->getHeight() + (font_size * padding_h_scalar);
}

void MenuOption::setSelected(bool selected)
{
	is_selected = selected;
}

SDL_Rect* MenuOption::getButtonRect()
{
	return buttonRenderQuad;
}

void MenuOption::render(int x, int y)
{
	SDL_Point* rotate_center = new SDL_Point();
	rotate_center->x = 0;
	rotate_center->y = 0;

	//Determine which button texture to use
	if(is_selected)
		buttonTextureSelected->render(x,y, NULL, 0, rotate_center, SDL_FLIP_NONE, buttonRenderQuad);
	else
		buttonTexture->render(x,y, NULL, 0, rotate_center, SDL_FLIP_NONE, buttonRenderQuad);
	textTexture->render(x + (font_size * padding_w_scalar)/2, y + buttonRenderQuad->h/3, NULL, 0, rotate_center, SDL_FLIP_NONE);

}

MenuOption::~MenuOption()
{
	TTF_CloseFont(font);
	textTexture->free();
	buttonTexture->free();
	buttonTextureSelected->free();
}
