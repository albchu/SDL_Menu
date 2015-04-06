#include "SDL_Texture_Wrapper.h"


SDL_Texture_Wrapper::SDL_Texture_Wrapper(SDL_Renderer* new_gRenderer)
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	renderer = new_gRenderer;
}

SDL_Texture_Wrapper::~SDL_Texture_Wrapper()
{
	//Deallocate
	free();
}

bool SDL_Texture_Wrapper::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool SDL_Texture_Wrapper::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return mTexture != NULL;
}

void SDL_Texture_Wrapper::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void SDL_Texture_Wrapper::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void SDL_Texture_Wrapper::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void SDL_Texture_Wrapper::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void SDL_Texture_Wrapper::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* renderQuad)
{
	if(renderQuad == NULL)
	{
		renderQuad = new SDL_Rect();
		//Set rendering space and render to screen
		renderQuad->x = x;
		renderQuad->y = y;
		renderQuad->w = mWidth;
		renderQuad->h = mHeight;
	}
	else
	{
		renderQuad->x = x;
		renderQuad->y = y;
	}

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad->w = clip->w;
		renderQuad->h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, mTexture, clip, renderQuad, angle, center, flip );
}

int SDL_Texture_Wrapper::getWidth()
{
	return mWidth;
}

int SDL_Texture_Wrapper::getHeight()
{
	return mHeight;
}