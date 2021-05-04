#include "Game.h"

Game::Game()
{
    score_val = 0;
    best_score = 0;

    gWindow = NULL;
    gRenderer = NULL;

    for( int i = 0; i < 5; i++)
    {
        gMusic[i] = NULL;
    }
}

Game::~Game()
{
    //Free the sound
    for( int i = 0; i < 4; i++)
    {
        Mix_FreeChunk( gMusic[i] );
    }

    for( int i = 0; i < 4; i++)
    {
        gMusic[i] = NULL;
    }

    //Free loaded images
	gBackground.free();
	play.free();
	pause.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

// function load libraries used in the game, create window && renderer
bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// Create window
		gWindow = SDL_CreateWindow( "Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

// function load images used in the main program in the game
bool Game::loadImage()
{
    bool success = true;

    // load background
    if( !gBackground.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	// load icon ở trạng thái đang chơi
    if( !play.loadFromFile( "image/play_icon.png", gRenderer ) )
	{
		printf( "Failed to load play_icon texture!\n" );
		success = false;
	}

	// load icon ở trạng thái pause
    if( !pause.loadFromFile( "image/pause_icon.png", gRenderer ) )
	{
		printf( "Failed to load pause_icon texture!\n" );
		success = false;
	}

    // load threat
    if( !gThreat[0].threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    if( !gThreat[1].threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    if( !gThreat[2].threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    return success;
}

// function load sounds used in the game
bool Game::loadMixer()
{
    bool success = true;

    //Load tap_to_play sound effect
	gMusic[0] = Mix_LoadWAV( "mixer/tap_to_play.wav" );
	if( gMusic[0] == NULL )
	{
		printf( "Failed to load tap_to_play sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load wing sound effect
	gMusic[1] = Mix_LoadWAV( "mixer/wing.wav" );
	if( gMusic[1] == NULL )
	{
		printf( "Failed to load wing sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load mark sound effect
	gMusic[2] = Mix_LoadWAV( "mixer/score.wav" );
	if( gMusic[2] == NULL )
	{
		printf( "Failed to load score sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load collision sound effect
	gMusic[3] = Mix_LoadWAV( "mixer/collision.wav" );
	if( gMusic[3] == NULL )
	{
		printf( "Failed to load collision sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    return success;
}

// function to write the main program in the game
void Game::gamePlay()
{
    // variables adjust gameloop
    bool is_play_again = 1; // 1: play agian ; 0: exit
    bool quit = false;
    SDL_Event e;

    // shows the start screen at the start of the game
    int start_menu = gMenu.showStart( gRenderer, gMusic[0] );
    if( start_menu == 1 )
    {
        quit = true;
    }
    else
    {
        // show tap play screen
        int tap_play_menu = gMenu.showTapPlay( gRenderer );
        if( tap_play_menu == 1 )
        {
            quit = true;
        }

        // do-while loop handles option: play again or exit the game
        do
        {
            // set feature for threats
            gThreat[0].set_threat_height();
            gThreat[1].set_threat_height();
            gThreat[2].set_threat_height();

            // set co-ordinate at first for bird
            gBird.set_x_bird( 150 );
            gBird.set_y_bird( 150 );
            gBird.setFrameClips( gRenderer );

            // variable denotes speed of background at main play screen
            int x = 0;

            // variables denote score
            gScore.setColor( Text::WHITE_TEXT );
            score_val = 0;
            string score, best;
            bool collision = false; // biến = false nếu bird không va chạm với rect điểm; = true nếu va chạm
            bool addScore = true; // biến kiểm tra xem điểm có cộng thêm hay không

            // variables denote play/pause
            SDL_Rect icon_rect = { 50, 50, 40, 40 };
            int xpos = 0, ypos = 0; // tọa độ chuột trên màn hình
            int count = 0; // count chẵn thì ở trạng thái play; count lẻ thì ở trạng thái pause

            //While gameloop is running
            while( !quit )
            {
                //Handle events
                while( SDL_PollEvent(&e) != 0 )
                {
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    if( e.type == SDL_MOUSEMOTION )
                    {
                        SDL_GetMouseState( &xpos, &ypos );

                        if( checkFocusMouse( xpos, ypos, icon_rect ) )
                        {
                            gBird.is_click_icon = true;
                        }
                        else gBird.is_click_icon = false;
                    }

                    if( e.type == SDL_MOUSEBUTTONDOWN )
                    {
                        SDL_GetMouseState( &xpos, &ypos );

                        if( checkFocusMouse( xpos, ypos, icon_rect ) )
                        {
                            Mix_PlayChannel( -1, gMusic[0], 0 );
                            count++;
                        }
                    }

                    gBird.handleEvents( e, gMusic[1] );
                }

                SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
                SDL_RenderClear( gRenderer );

                // set velocity for background
                if( count % 2 == 1 ) x -= 0;
                else x -= 4;

                // render background
                gBackground.render( gRenderer, x, 0 );
                gBackground.render( gRenderer, SCREEN_WIDTH + x, 0 );

                if( -x == SCREEN_WIDTH ) x = 0;

                // render threats on the screen
                if( gThreat[0].x_threat >= 0 )
                {
                    gThreat[1].x_threat = gThreat[0].x_threat + SCREEN_WIDTH / 3;
                    gThreat[2].x_threat = gThreat[1].x_threat + SCREEN_WIDTH / 3;
                }
                else
                {
                    gThreat[0] = gThreat[1];
                    gThreat[1] = gThreat[2];
                    gThreat[2].set_threat_height();
                }

                for( int i = 0; i < 3; i++ )
                {
                    gThreat[i].renderThreat( gRenderer );
                }

                // render play, pause icon and handle play/pause option
                play.render( gRenderer, icon_rect.x, icon_rect.y );
                if( count % 2 == 1 )
                {
                    pause.render( gRenderer, icon_rect.x, icon_rect.y );
                    for( int i = 0; i < 3; i++ )
                    {
                        gThreat[i].pause_threat = true;
                    }
                    gBird.pause_bird = true;
                }
                else
                {
                    play.render( gRenderer, icon_rect.x, icon_rect.y );
                    for( int i = 0; i < 3; i++ )
                    {
                        gThreat[i].pause_threat = false;
                    }
                    gBird.pause_bird = false;
                }

                // handle bird move and render bird
                gBird.handleMoveBird();
                gBird.renderBird( gRenderer );

                // check collision between bird and threats
                for( int i = 0; i < 3; i++ )
                {
                    bool check1 = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectCol1() );
                    bool check2 = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectCol2() );
                    if( check1 || check2 )
                    {
                        Mix_PlayChannel( -1, gMusic[3] , 0);
                        quit = true;
                        break;
                    }
                }

                // check collision between bird and edges of the screen
                if( gBird.get_y_bird() + 33 < 0 || gBird.get_y_bird() + 67 > GROUND_HEIGHT )
                {
                    Mix_PlayChannel( -1, gMusic[3] , 0);
                    quit = true;
                }

                // handle score
                for( int i = 0; i < 3; i++ )
                {
                    bool check = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectBlank() );
                    if( check == true )
                    {
                        collision = true;
                        break;
                    }
                    else collision = false;
                }

                if( collision == true )
                {
                    if( addScore == true )
                    {
                        score_val++;
                        Mix_PlayChannel( -1, gMusic[2], 0);
                    }
                    addScore = false;
                }
                else addScore = true;

                score = to_string( score_val );

                // show score on the screen
                gScore.loadText( score, gRenderer, 50 );
                gScore.renderText( gRenderer, SCREEN_WIDTH / 2, 100 );

                SDL_RenderPresent( gRenderer );
            }

            if( best_score < score_val ) best_score = score_val;
            best = to_string( best_score );

            // show the gameover screen when the game is lost
            int gameover_menu = gMenu.showGameOver( gRenderer, gMusic[0], score , best );

            if( gameover_menu == 0 )
            {
                quit = false;
                is_play_again = 1;
                gMenu.showTapPlay( gRenderer );
            }
            else is_play_again = 0;

        }while( is_play_again != 0 );
    }
}
