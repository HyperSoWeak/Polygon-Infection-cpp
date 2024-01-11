#include "Source.h"

ALLEGRO_BITMAP *Source::soldier_image = nullptr;
ALLEGRO_BITMAP *Source::archer_image = nullptr;
ALLEGRO_BITMAP *Source::speedy_image = nullptr;
ALLEGRO_BITMAP *Source::tank_image = nullptr;
ALLEGRO_BITMAP *Source::split_image = nullptr;
ALLEGRO_BITMAP *Source::summoner_image = nullptr;
ALLEGRO_BITMAP *Source::healer_image = nullptr;

ALLEGRO_BITMAP *Source::bullet_blue_image = nullptr;
ALLEGRO_BITMAP *Source::bullet_green_image = nullptr;

ALLEGRO_BITMAP *Source::player_base_image = nullptr;
ALLEGRO_BITMAP *Source::player_barrel_image = nullptr;

ALLEGRO_BITMAP *Source::particle_image = nullptr;

ALLEGRO_SAMPLE *Source::menu_bgm = nullptr;
ALLEGRO_SAMPLE *Source::game_bgm = nullptr;

ALLEGRO_SAMPLE *Source::button_click = nullptr;
ALLEGRO_SAMPLE *Source::gameover_music = nullptr;
ALLEGRO_SAMPLE *Source::shoot_sfx = nullptr;
ALLEGRO_SAMPLE *Source::explode_sfx = nullptr;
ALLEGRO_SAMPLE *Source::respawn_sfx = nullptr;

ALLEGRO_FONT *Source::test_font = nullptr;

void Source::load_source() {
    soldier_image = al_load_bitmap("image/enemy/Soldier.png");
    archer_image = al_load_bitmap("image/enemy/Archer.png");
    speedy_image = al_load_bitmap("image/enemy/Speedy.png");
    tank_image = al_load_bitmap("image/enemy/Tank.png");
    split_image = al_load_bitmap("image/enemy/Split.png");
    summoner_image = al_load_bitmap("image/enemy/Summoner.png");
    healer_image = al_load_bitmap("image/enemy/Healer.png");

    bullet_blue_image = al_load_bitmap("image/bullets/bullet_blue.png");
    bullet_green_image = al_load_bitmap("image/bullets/bullet_green.png");

    player_base_image = al_load_bitmap("image/player/Base.png");
    player_barrel_image = al_load_bitmap("image/player/Barrel.png");

    particle_image = al_load_bitmap("image/Particle.png");

    menu_bgm = al_load_sample("audio/menu.ogg");
    game_bgm = al_load_sample("audio/game.ogg");

    button_click = al_load_sample("audio/button.wav");
    gameover_music = al_load_sample("audio/gameover.wav");
    shoot_sfx = al_load_sample("audio/shoot.wav");
    explode_sfx = al_load_sample("audio/explosion.wav");
    respawn_sfx = al_load_sample("audio/respawn.wav");

    test_font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 30, 0);
}

void Source::destroy_source() {
    al_destroy_bitmap(soldier_image);
    al_destroy_bitmap(archer_image);
    al_destroy_bitmap(speedy_image);
    al_destroy_bitmap(tank_image);
    al_destroy_bitmap(split_image);
    al_destroy_bitmap(summoner_image);
    al_destroy_bitmap(healer_image);

    al_destroy_bitmap(bullet_blue_image);
    al_destroy_bitmap(bullet_green_image);
    
    al_destroy_bitmap(player_base_image);
    al_destroy_bitmap(player_barrel_image);

    al_destroy_bitmap(particle_image);

    al_destroy_sample(menu_bgm);
    al_destroy_sample(game_bgm);

    al_destroy_sample(button_click);
    al_destroy_sample(gameover_music);
    al_destroy_sample(shoot_sfx);
    al_destroy_sample(explode_sfx);
    al_destroy_sample(respawn_sfx);

    al_destroy_font(test_font);
}