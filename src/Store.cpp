#include "Store.h"

Store::Store() {}

void Store::init() {
    current_tab = TOWER_TAB;

    tower_tab = new UpgradeTab(Vector2(995, 40), (char *)"image/icon/tower.png");
    player_tab = new UpgradeTab(Vector2(995, 150), (char *)"image/icon/player.png");
    bullet_tab = new UpgradeTab(Vector2(995, 260), (char *)"image/icon/bullet.png");

    tower_max_health_upgrade = new Upgrade(Vector2(1165, 120), 10, 1.6, (char *)"Max Health");
    tower_regeneration_upgrade = new Upgrade(Vector2(1165, 280), 40, 1.8, (char *)"Regeneration");
    tower_fire_rate_upgrade = new Upgrade(Vector2(1165, 440), 15, 1.3, (char *)"Fire Rate");
    tower_range_upgrade = new Upgrade(Vector2(1165, 600), 15, 1.8, (char *)"Detect Range");

    player_max_health_upgrade = new Upgrade(Vector2(1165, 120), 10, 1.6, (char *)"Max Health");
    player_regeneration_upgrade = new Upgrade(Vector2(1165, 280), 30, 2.3, (char *)"Regeneration");
    player_fire_rate_upgrade = new Upgrade(Vector2(1165, 440), 15, 1.3, (char *)"Fire Rate");
    player_speed_upgrade = new Upgrade(Vector2(1165, 600), 10, 2.7, (char *)"Move Speed");

    bullet_damage_upgrade = new Upgrade(Vector2(1165, 120), 150, 2.4, (char *)"Damage");
    bullet_speed_upgrade = new Upgrade(Vector2(1165, 280), 200, 2.1, (char *)"Speed");

    store_bitmap = al_load_bitmap("image/Store.png");

    font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 40, 0);
}

void Store::update(int &coins) {
    tower_tab->update();
    player_tab->update();
    bullet_tab->update();

    switch(current_tab) {

    case TOWER_TAB:
        tower_max_health_upgrade->update(coins);
        tower_regeneration_upgrade->update(coins);
        tower_fire_rate_upgrade->update(coins);
        tower_range_upgrade->update(coins);
        break;

    case PLAYER_TAB:
        player_max_health_upgrade->update(coins);
        player_regeneration_upgrade->update(coins);
        player_fire_rate_upgrade->update(coins);
        player_speed_upgrade->update(coins);
        break;

    case BULLET_TAB:
        bullet_damage_upgrade->update(coins);
        bullet_speed_upgrade->update(coins);
        break;

    }
}

void Store::render() {
    tower_tab->render();
    player_tab->render();
    bullet_tab->render();

    al_draw_bitmap(store_bitmap, 1100, 0, 0);

    switch(current_tab) {

    case TOWER_TAB:
        tower_max_health_upgrade->render();
        tower_regeneration_upgrade->render();
        tower_fire_rate_upgrade->render();
        tower_range_upgrade->render();
        break;

    case PLAYER_TAB:
        player_max_health_upgrade->render();
        player_regeneration_upgrade->render();
        player_fire_rate_upgrade->render();
        player_speed_upgrade->render();
        break;

    case BULLET_TAB:
        bullet_damage_upgrade->render();
        bullet_speed_upgrade->render();
        break;

    }

    char *text = new char[30];

    if(current_tab == TOWER_TAB) text = (char *)"Tower Upgrade";
    else if(current_tab == PLAYER_TAB) text = (char *)"Player Upgrade";
    else if(current_tab == BULLET_TAB) text = (char *)"Bullet Upgrade";

    al_draw_text(font, al_map_rgb(255, 255, 255), 1300, 30, 1, text);
}

void Store::handleInput(Tower &tower, Player &player) {
    if(tower_tab->isClicked()) current_tab = TOWER_TAB;
    else if(player_tab->isClicked()) current_tab = PLAYER_TAB;
    else if(bullet_tab->isClicked()) current_tab = BULLET_TAB;

    switch(current_tab) {

    case TOWER_TAB:
        if(tower_max_health_upgrade->isUpgraded()) {
            tower.incMaxHealth(tower.max_health * 0.1 + tower_max_health_upgrade->level * 3);
        }

        if(tower_regeneration_upgrade->isUpgraded()) {
            tower.regeneration *= 1.4;
        }

        if(tower_fire_rate_upgrade->isUpgraded()) {
            tower.incFireRate(tower.fire_rate * (0.5 / (((float)tower_fire_rate_upgrade->level + 1) / 2)));
        }

        if(tower_range_upgrade->isUpgraded()) {
            tower.incRange(20 / ((float)(tower_range_upgrade->level + 6) / 7));
        }

        break;

    case PLAYER_TAB:
        if(player_max_health_upgrade->isUpgraded()) {
            player.incMaxHealth(player.max_health * 0.1 + player_max_health_upgrade->level * 3);
        }

        if(player_regeneration_upgrade->isUpgraded()) {
            player.regeneration *= 1.4;
        }

        if(player_fire_rate_upgrade->isUpgraded()) {
            player.incFireRate(player.fire_rate * (0.35 / (((float)player_fire_rate_upgrade->level + 1) / 2)));
        }

        if(player_speed_upgrade->isUpgraded()) {
            player.speed *= 1.1;
        }

        break;

    case BULLET_TAB:
        if(bullet_damage_upgrade->isUpgraded()) {
            Bullet::incDamage(0.7);
        }
        if(bullet_speed_upgrade->isUpgraded()) {
            Bullet::mulSpeed(1.15);
        }
        break;

    }
}

void Store::destroy() {
    al_destroy_bitmap(store_bitmap);
    al_destroy_font(font);
}
