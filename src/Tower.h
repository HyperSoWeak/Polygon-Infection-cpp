#pragma once

#include "Math.h"
#include "Bullet.h"
#include "Bar.h"
#include <allegro5/allegro.h>
#include <vector>

class Tower {

public:
    Tower();
    void init();
    bool update(Vector2);
    void render();
    void handleInput();
    void destroy();

    void fireBullet(Vector2);

    Vector2 getPosition();
    float radius;
    float detect_range;
    std::vector<Bullet*> getBullets();
    void gothit(int);

    void incMaxHealth(int amount);
    void incRegen(int amount);
    void incFireRate(float amount);
    void incRange(float amount);

    float fire_rate;
    int damage;
    float regeneration;
    int max_health;
    
private:
    Vector2 pos;
    Vector2 bar_offset;

    int health;
    Bar health_bar;

    std::vector<Bullet*> bullets;

    ALLEGRO_TIMER *bullet_timer;
    ALLEGRO_TIMER *regen_timer;
    ALLEGRO_EVENT_QUEUE *event_queue;

    // render
    ALLEGRO_BITMAP *base_bitmap;
    ALLEGRO_BITMAP *cannon_bitmap;
    ALLEGRO_BITMAP *barrel_bitmap;
    
    int base_width;
    int base_height;
    int barrel_height;
    int barrel_width;
    int cannon_radius;

    float facing_angle;

};