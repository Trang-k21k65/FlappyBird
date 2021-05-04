#include "Game.h"

using namespace std;

int main( int argc, char* args[] )
{
    Game gGame;

    if( !gGame.init() )
    {
        printf( "Failed to initialize!\n" );
    }

    if( !gGame.loadImage() )
    {
        printf( "Failed to load image!\n" );
    }

    if( !gGame.loadMixer() )
    {
        printf( "Failed to load mixer!\n" );
    }

    gGame.gamePlay();

    return 0;
}



