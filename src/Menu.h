#pragma once

#include "State.h"
#include "Button.h"
#include "Global.h"
#include "Source.h"

class Menu : public State {

public:
    Menu();
    void init();
    void update();
    void render();
    void handleInput(GAME_STATE &);
    void destroy();
    void stop_music();

private:
    Button *start;
    Button *about;
    Button *exit;

    ALLEGRO_FONT *font;
    
    ALLEGRO_BITMAP *background;

    ALLEGRO_SAMPLE_ID bgm_id;

};