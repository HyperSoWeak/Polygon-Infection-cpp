#pragma once

#include "State.h"
#include "Player.h"
#include "Tower.h"
#include "Upgrade.h"
#include "UpgradeTab.h"
#include "Wave.h"
#include "Store.h"
#include "ParticleHandler.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Game : public State {

public:
    Game();
    void init();
    void update();
    void render();
    void handleInput(GAME_STATE &);
    void destroy();
    void stop_music();

    int get_wave_num();

    int coins;
    int score;

private:
    ALLEGRO_TIMER *rest;
    
    Player player;
    Tower tower;
    Wave wave;
    Store store;

    ALLEGRO_FONT *info_font;

    ALLEGRO_COLOR bg_color = al_map_rgb(200, 200, 200);

    bool alive;

    ALLEGRO_SAMPLE_ID bgm_id;

    ParticleHandler *particle_handler;

};