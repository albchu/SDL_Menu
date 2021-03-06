#include "MenuOption.h"

//TODO: Enhancement: pass in textures for buttons rather than recreate them every goddamn time
MenuOption::MenuOption(SDL_Renderer* new_renderer, const char* init_id, const char* new_text, int new_font_size, const char* font_path)
{
	//text = new_text;
	id = init_id;
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

	buttonRenderQuad = new SDL_Rect();	// Init button rect 

	// Load text
	set_text(new_text);

	// Load background button
	set_button_texture("../data/images/Menu/glossy_button_blank_black_rectangle.bmp");

	// Load background selected button
	if( !buttonTextureSelected->loadFromFile("../data/images/Menu/glossy_button_blank_yellow_rectangle.bmp") )
	{
		printf( "Failed to render button texture!\n" );
	}

	////Set rendering space and render to screen
	//buttonRenderQuad->w = textTexture->getWidth() + (font_size * padding_w_scalar);
	//buttonRenderQuad->h = textTexture->getHeight() + (font_size * padding_h_scalar);
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

SDL_Texture_Wrapper* MenuOption::get_text_texture()
{
	return textTexture;
}

void MenuOption::set_button_texture(const char* texture_path)
{
		// Load background button
	if( !buttonTexture->loadFromFile(texture_path) )
	{
		printf( "Failed to render button texture!\n" );
	}
}

void MenuOption::set_button_selected_texture(const char* texture_path)
{
		// Load background button
	if( !buttonTextureSelected->loadFromFile(texture_path) )
	{
		printf( "Failed to render button texture!\n" );
	}
}

MenuOption::MenuOption()
{
}

MenuOption::~MenuOption()
{
	TTF_CloseFont(font);
	textTexture->free();
	buttonTexture->free();
	buttonTextureSelected->free();
}

void MenuOption::set_option_data(const char* menu_name)
{
	type = REDIRECT;
	redirect_menu = menu_name;
}

void MenuOption::set_option_data(bool& new_flag)
{
	type = FLAG;
	flag = &new_flag;
}

const char* MenuOption::get_redirect_menu()
{
	return redirect_menu;
}

bool MenuOption::get_flag()
{
	return flag;
}

const char* MenuOption::get_text()
{
	return text;
}

void MenuOption::set_text(const char* new_text)
{
	text = new_text;

	// Reload the texture
	SDL_Color textColor = { 0, 0, 0 };
	if( !textTexture->loadFromRenderedText( text, textColor, font ) )
	{
		printf( "Failed to render text texture!\n" );
	}

	//Resize the box texture
	buttonRenderQuad->w = textTexture->getWidth() + (font_size * padding_w_scalar);
	buttonRenderQuad->h = textTexture->getHeight() + (font_size * padding_h_scalar);
}

OptionType MenuOption::get_type()
{
	return type;
}

void MenuOption::toggle_flag()
{
	*flag = !*flag;
}

const char* MenuOption::get_id()
{
	return id;
}

