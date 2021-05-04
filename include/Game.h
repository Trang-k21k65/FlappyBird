#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "Bird.h"
#include <typeinfo>

class Game : public LTexture
{
    public:
        Game();
        virtual ~Game();

        bool init();
        bool loadImage();
        bool loadMixer();
        void gamePlay();

    private:
        Bird gBird;
        Threat gThreat[3];
        Text gScore;
        Menu gMenu;

        LTexture gBackground;
        LTexture play, pause;

        int score_val;
        int best_score;

        Mix_Chunk* gMusic[4];
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
};

#endif // GAME_H
