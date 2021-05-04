#include "Menu.h"

Menu::Menu()
{
    speed = 0;

    x_mouse = 0;
    y_mouse = 0;
}

Menu::~Menu()
{
    bgr.free();

    logo.free();
    get_ready.free();
    tap.free();
    gameover.free();

    start_rect.free();
    gameover_rect.free();

    SDL_Quit();
}

// hàm vẽ màn hình start: trả về 1 là exit; trả về 0 là play
int Menu::showStart( SDL_Renderer* gRenderer, Mix_Chunk* tap )
{
    // load background cho man hinh start
    if( !bgr.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background start menu texture!\n" );
		return 1;
	}

	// load logo
    if( !logo.loadFromFile( "image/logo.png", gRenderer ) )
	{
		printf( "Failed to load logo texture!\n" );
		return 1;
	}

    // load rect chua text option
    if( !start_rect.loadFromFile( "image/start_rect.png", gRenderer ) )
	{
		printf( "Failed to load start_rect texture!\n" );
		return 1;
	}

    // Set rect chi start_rect
	start_pos[0].x = (SCREEN_WIDTH - START_WIDTH) / 2;
	start_pos[0].y = 400;
	start_pos[0].h = START_HEIGHT;
	start_pos[0].w = START_WIDTH;

	start_pos[1].x = (SCREEN_WIDTH - START_WIDTH) / 2;
	start_pos[1].y = 500;
	start_pos[1].h = START_HEIGHT;
	start_pos[1].w = START_WIDTH;

	// Set text trong man hinh start
	start_text[0].setColor( Text::ORANGE_TEXT );
	start_text[0].loadText( "Play", gRenderer, 30 );

	start_text[1].setColor( Text::ORANGE_TEXT );
	start_text[1].loadText( "Exit", gRenderer, 30 );

	while(true)
    {
        while( SDL_PollEvent( &mouse_event ) != 0 )
        {
            switch( mouse_event.type )
            {
                case SDL_QUIT:
                    return 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState( &x_mouse, &y_mouse );

                    for( int i = 0; i < option; i++ )
                    {
                        if( checkFocusMouse( x_mouse, y_mouse, start_pos[i] ) )
                        {
                            Mix_PlayChannel( -1, tap, 0);
                            return i;
                        }
                    }
                    break;

                case SDL_KEYDOWN:
                    if( mouse_event.key.keysym.sym == SDLK_ESCAPE )
                    {
                        return 1;
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
        SDL_RenderClear( gRenderer );

        speed -= 4;

        // render background start
        bgr.render( gRenderer, speed, 0 );
        bgr.render( gRenderer, SCREEN_WIDTH + speed, 0 );

        if( -speed == SCREEN_WIDTH ) speed = 0;

        // render logo
        logo.render( gRenderer, 95, 130 );

        // render start_rect
        start_rect.render( gRenderer, start_pos[0].x, start_pos[0].y);
        start_rect.render( gRenderer, start_pos[1].x, start_pos[1].y);

        // render start_text
        start_text[0].renderText( gRenderer, start_pos[0].x + 28, start_pos[0].y + 23 );
        start_text[1].renderText( gRenderer, start_pos[1].x + 34, start_pos[1].y + 23 );

        SDL_RenderPresent( gRenderer );
    }

    return 1;
}

// hàm vẽ màn hình tap: trả về 1 là load ảnh failed; trả về 0 là bắt đầu chơi
int Menu::showTapPlay( SDL_Renderer* gRenderer )
{
    // load background cho man hinh tap play
    if( !bgr.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background tap play texture!\n" );
		return 1;
	}

    // load get_ready cho tap play
    if( !get_ready.loadFromFile( "image/get_ready.png", gRenderer ) )
	{
		printf( "Failed to load get_ready texture!\n" );
		return 1;
	}

	// load tap
    if( !tap.loadFromFile( "image/tap.png", gRenderer ) )
	{
		printf( "Failed to load tap texture!\n" );
		return 1;
	}

	while(true)
    {
        while( SDL_PollEvent( &mouse_event ) != 0 )
        {
            switch( mouse_event.type )
            {
                case SDL_QUIT:
                    return 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    return 0;
                    break;

                case SDL_KEYDOWN:
                    if( mouse_event.key.keysym.sym == SDLK_ESCAPE )
                    {
                        return 1;
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
        SDL_RenderClear( gRenderer );

        speed -= 4;

        // render background cho tap play
        bgr.render( gRenderer, speed, 0 );
        bgr.render( gRenderer, SCREEN_WIDTH + speed, 0 );

        if( -speed == SCREEN_WIDTH ) speed = 0;

        // render get_ready
        get_ready.render( gRenderer, 0, 100 );

        // render tap
        tap.render( gRenderer, ( SCREEN_WIDTH - tap.getWidth() ) / 2, 400 );

        SDL_RenderPresent( gRenderer );
    }

    return 1;
}

// hàm vẽ màn hình gameover: trả về 1 là exit; trả về 0 là play
int Menu::showGameOver( SDL_Renderer* gRenderer, Mix_Chunk* tap, string mark, string best_mark )
{
    // load background cho man hinh gameover
    if( !bgr.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background gameover texture!\n" );
		return 1;
	}

	// load gameover logo
    if( !gameover.loadFromFile( "image/gameover.png", gRenderer ) )
	{
		printf( "Failed to load gameover texture!\n" );
		return 1;
	}

    // load rect chua gameover_text
    if( !gameover_rect.loadFromFile( "image/gameover_rect.png", gRenderer ) )
	{
		printf( "Failed to load gameover_rect texture!\n" );
		return 1;
	}

    // Set rect chi gameover_rect
	gameover_pos[0].x = 130;
	gameover_pos[0].y = 480;
	gameover_pos[0].h = GAMEOVER_HEIGHT;
	gameover_pos[0].w = GAMEOVER_WIDTH;

	gameover_pos[1].x = 370;
	gameover_pos[1].y = 480;
	gameover_pos[1].h = GAMEOVER_HEIGHT;
	gameover_pos[1].w = GAMEOVER_WIDTH;

	// Set text trong man hinh gameover
	gameover_text[0].setColor( Text::GREEN_TEXT );
	gameover_text[0].loadText( "Play", gRenderer, 30 );

	gameover_text[1].setColor( Text::GREEN_TEXT );
	gameover_text[1].loadText( "Exit", gRenderer, 30 );

	gameover_text[2].setColor( Text::GREEN_TEXT );
	gameover_text[2].loadText( "Score", gRenderer, 30 );

	gameover_text[3].setColor( Text::GREEN_TEXT );
	gameover_text[3].loadText( "Best", gRenderer, 30 );

	// Set mark_text
	mark_text[0].setColor( Text::ORANGE_TEXT );
	mark_text[0].loadText( mark, gRenderer, 30 );

	mark_text[1].setColor( Text:: ORANGE_TEXT );
	mark_text[1].loadText( best_mark, gRenderer, 30 );

	while( true )
    {
        while( SDL_PollEvent( &mouse_event ) != 0 )
        {
            switch( mouse_event.type )
            {
                case SDL_QUIT:
                    return 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState( &x_mouse, &y_mouse );

                    for( int i = 0; i < option; i++ )
                    {
                        if( checkFocusMouse( x_mouse, y_mouse, gameover_pos[i] ) )
                        {
                            Mix_PlayChannel( -1, tap, 0);
                            return i;
                        }
                    }
                    break;

                case SDL_KEYDOWN:
                    if( mouse_event.key.keysym.sym == SDLK_ESCAPE )
                    {
                        return 1;
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
        SDL_RenderClear( gRenderer );

        bgr.render( gRenderer, 0, 0 );
        gameover.render( gRenderer, 50, 52 );

        // render gameover_rect
        gameover_rect.render( gRenderer, gameover_pos[0].x, gameover_pos[0].y);
        gameover_rect.render( gRenderer, gameover_pos[1].x, gameover_pos[1].y);
        gameover_rect.render( gRenderer, 130, 350 );
        gameover_rect.render( gRenderer, 370, 350 );

        // render gameover_text
        gameover_text[0].renderText( gRenderer, gameover_pos[0].x + 45, gameover_pos[0].y + 31 );
        gameover_text[1].renderText( gRenderer, gameover_pos[1].x + 50, gameover_pos[1].y + 31 );
        gameover_text[2].renderText( gRenderer, 130 + 37, 350 + 13 );
        gameover_text[3].renderText( gRenderer, 370 + 50, 350 + 13 );

        // render mark_text
        mark_text[0].renderText( gRenderer, 130 + 85, 350 + 50);
        mark_text[1].renderText( gRenderer, 370 + 85, 350 + 50);

        SDL_RenderPresent( gRenderer );

    }

    return 1;
}
