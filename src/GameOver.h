#pragma once

#include "State.h"
#include "Button.h"
#include "Global.h"
#include "Game.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

class GameOver : public State {

public:
    GameOver(Game *game);
    void init();
    void update();
    void render();
    void handleInput(GAME_STATE &);
    void destroy();
    void stop_music();

private:
    Button *restart;
    Button *menu;

    ALLEGRO_TIMER *fade_timer;

    ALLEGRO_FONT *title_font;
    ALLEGRO_FONT *info_font;

    bool fading;

    Game *game;

};