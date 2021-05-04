#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Config.h"

using namespace std;

class LTexture
{
	public:
		LTexture();
		virtual ~LTexture();

		bool loadFromFile( string path, SDL_Renderer* gRenderer );
		bool loadFromRenderedText( string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font *gFont );
		void free();
		void render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                     SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        bool checkFocusMouse( int& x, int& y, SDL_Rect& rect);

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};

#endif // LTEXTURE_H
