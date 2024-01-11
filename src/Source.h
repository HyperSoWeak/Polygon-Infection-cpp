#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Source {

public:
    static void load_source();
    static void destroy_source();

    static ALLEGRO_BITMAP *soldier_image;
    static ALLEGRO_BITMAP *archer_image;
    static ALLEGRO_BITMAP *speedy_image;
    static ALLEGRO_BITMAP *tank_image;
    static ALLEGRO_BITMAP *split_image;
    static ALLEGRO_BITMAP *summoner_image;
    static ALLEGRO_BITMAP *healer_image;

    static ALLEGRO_BITMAP *bullet_blue_image;
    static ALLEGRO_BITMAP *bullet_green_image;

    static ALLEGRO_BITMAP *player_base_image;
    static ALLEGRO_BITMAP *player_barrel_image;

    static ALLEGRO_BITMAP *particle_image;

    static ALLEGRO_SAMPLE *menu_bgm;
    static ALLEGRO_SAMPLE *game_bgm;

    static ALLEGRO_SAMPLE *button_click;
    static ALLEGRO_SAMPLE *gameover_music;
    static ALLEGRO_SAMPLE *shoot_sfx;
    static ALLEGRO_SAMPLE *explode_sfx;
    static ALLEGRO_SAMPLE *respawn_sfx;

    static ALLEGRO_FONT *test_font;

};