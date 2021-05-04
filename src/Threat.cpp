#include "Threat.h"

Threat::Threat()
{
    x_threat = SCREEN_WIDTH;
    pause_threat = false;
}

Threat::~Threat()
{
    threat.free();
}

// hàm set chiều cao bỏ đi của threats
void Threat::set_threat_height()
{
    x_threat = SCREEN_WIDTH;
    int height = rand() % 300;
    threat_height = height;
}

// hàm vẽ threats lên màn hình
void Threat::renderThreat( SDL_Renderer *gRenderer )
{
    clipThreat.x = 0;
    clipThreat.y = threat_height;
    clipThreat.w = threat.getWidth();
    clipThreat.h = GROUND_HEIGHT;

    if( !pause_threat ) x_threat -= 3;

    threat.render( gRenderer, x_threat, 0, &clipThreat);
}

// hàm lấy các chỉ số của rect of threat trên
SDL_Rect Threat::get_RectCol1()
{
    SDL_Rect rect;

    rect.x = x_threat + 1;
    rect.y = 6;
    rect.w = threat.getWidth();
    rect.h = THREAT_HEIGHT - threat_height;

    return rect;
}

// hàm lấy các chỉ số của rect of threat dưới
SDL_Rect Threat::get_RectCol2()
{
    SDL_Rect rect;

    rect.x = x_threat + 1;
    rect.y = BLANK + THREAT_HEIGHT - threat_height - 6;
    rect.w = threat.getWidth();
    rect.h = GROUND_HEIGHT - rect.y;

    return rect;
}

// hàm lấy các chỉ số của rect điểm: khi bird va chạm với nó (chỉ tính 1 lần) thì cộng thêm 1 điểm
SDL_Rect Threat::get_RectBlank()
{
    SDL_Rect rect;

    rect.x = x_threat + 52;
    rect.y = THREAT_HEIGHT - threat_height;
    rect.w = 10;
    rect.h = BLANK;

    return rect;
}
