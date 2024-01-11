#pragma once

#include "Math.h"
#include "Bullet.h"
#include "Tower.h"
#include "Bar.h"
#include "ParticleHandler.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>

class Player {

public:
    Player();
    void init();
    void update(Tower&, ParticleHandler*);
    void render();
    void handleInput();
    void destroy();

    void fireBullet();
    
    Vector2 getPosition();
    std::vector<Bullet*> getBullets();
    void gothit(int);
    
    int radius;
    bool alive;

    void incMaxHealth(int amount);
    void incRegen(int amount);
    void incFireRate(float amount);
    void incSpeed(float amount);
    
    float speed;
    float fire_rate;
    int max_health;
    float regeneration;

private:
    Vector2 pos;
    Vector2 direction;
    Vector2 vel;

    Vector2 mouse_pos;

    int health;
    
    int dmg;
    Bar health_bar;

    bool left;
    bool right;
    bool up;
    bool down;

    bool firing;

    ALLEGRO_KEYBOARD_STATE key_state;

    std::vector<Bullet*> bullets;

    ALLEGRO_TIMER *bullet_timer;
    ALLEGRO_TIMER *regen_timer;
    ALLEGRO_TIMER *respawn_timer;
    ALLEGRO_FONT *font;

    // render
    ALLEGRO_BITMAP *base_bitmap;
    ALLEGRO_BITMAP *barrel_bitmap;

    int barrel_height;
    int barrel_width;

    float facing;

};