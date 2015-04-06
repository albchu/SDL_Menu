#ifndef _SDL_TEXTURE_WRAPPER_H
#define _SDL_TEXTURE_WRAPPER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//Texture wrapper class
class SDL_Texture_Wrapper
{
public:
	//Initializes variables
	SDL_Texture_Wrapper(SDL_Renderer* new_renderer);

	//Deallocates memory
	~SDL_Texture_Wrapper();

	//Loads image at specified path
	bool loadFromFile( std::string path );

	//Creates image from font string
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont );

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );

	//Renders texture at given point
	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect* renderQuad = NULL );

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
	SDL_Renderer* renderer;
};

#endif