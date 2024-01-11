#pragma once

#include "Upgrade.h"
#include "UpgradeTab.h"
#include "Tower.h"
#include "Player.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

enum TAB_TYPE {
    TOWER_TAB,
    PLAYER_TAB,
    BULLET_TAB
};

class Store {

public:
    Store();
    void init();
    void update(int &coins);
    void render();
    void handleInput(Tower &tower, Player &player);
    void destroy();

    TAB_TYPE current_tab;

private:
    UpgradeTab *tower_tab;
    UpgradeTab *player_tab;
    UpgradeTab *bullet_tab;

    // Tower
    Upgrade *tower_max_health_upgrade;
    Upgrade *tower_regeneration_upgrade;
    Upgrade *tower_fire_rate_upgrade;
    Upgrade *tower_range_upgrade;

    // Player
    Upgrade *player_max_health_upgrade;
    Upgrade *player_regeneration_upgrade;
    Upgrade *player_fire_rate_upgrade;
    Upgrade *player_speed_upgrade;

    // Bullet
    Upgrade *bullet_damage_upgrade;
    Upgrade *bullet_speed_upgrade;

    ALLEGRO_BITMAP *store_bitmap;

    ALLEGRO_FONT *font;

};