#include "Text.h"

Text::Text()
{
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;

    gFont = NULL;
}

Text::~Text()
{
    text.free();

    TTF_CloseFont( gFont );
	gFont = NULL;

	TTF_Quit();
}

// hàm đặt màu cho text
void Text::setColor( const int& type )
{
    if( type == WHITE_TEXT )
    {
        textColor = { 255, 255, 255 };
    }

    if( type == ORANGE_TEXT )
    {
        textColor = { 255, 117, 26 };
    }

    if( type == GREEN_TEXT )
    {
        textColor = { 0, 204, 0 };
    }
}

// hàm load chữ, cỡ chữ, font chữ
bool Text::loadText( string s, SDL_Renderer* gRenderer, int size )
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", size );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		if( !text.loadFromRenderedText( s, textColor, gRenderer, gFont ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}

	return success;
}

// hàm vẽ text lên màn hình
void Text::renderText( SDL_Renderer* gRenderer, int x_text, int y_text )
{
    text.render( gRenderer, x_text, y_text);
}
