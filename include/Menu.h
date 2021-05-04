#ifndef MENU_H
#define MENU_H

#include "Text.h"
#include "SDL_mixer.h"

#define START_HEIGHT 74
#define START_WIDTH 154

#define GAMEOVER_HEIGHT 96
#define GAMEOVER_WIDTH 200

class Menu: public LTexture
{
    public:
        Menu();
        virtual ~Menu();

        int showStart( SDL_Renderer* gRenderer, Mix_Chunk* tap);
        int showTapPlay( SDL_Renderer* gRenderer );
        int showGameOver( SDL_Renderer* gRenderer, Mix_Chunk* tap, string mark, string best_mark );

    private:
        // backgroung cho menu
        LTexture bgr;
        LTexture logo, get_ready, tap, gameover;

        // rect chua start_text, gameover_text
        LTexture start_rect, gameover_rect;

        // vi tri cua start_rect, gameover_rect tren man hinh
        SDL_Rect start_pos[option], gameover_pos[option];

        // text trong man hinh start, gameover
        Text start_text[option], gameover_text[option + 2], mark_text[2];

        // speed cho background khi ở màn hình menu
        int speed;

        // Mouse Events
        SDL_Event mouse_event;

        // vi tri cua chuot trong man hinh
        int x_mouse, y_mouse;

};

#endif // MENU_H
