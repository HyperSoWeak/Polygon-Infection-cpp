#pragma once

#include "Math.h"
#include "Global.h"
#include <allegro5/allegro.h>

enum COLOR {
    BLUE,
    GREEN
};

class Bullet {

public:
    Bullet(float x, float y, float angle, COLOR type);
    void init();
    void update();
    void render();
    bool isOffScreen();
    bool hit;
    static float speed;
    static float dmg;
    static void incDamage(int amount);
    static void incSpeed(float amount);
    static void mulSpeed(float amount);
    static void reset();

    Vector2 getPosition();
    int getDamage();

private:
    Vector2 pos;
    float angle;

    float dx;
    float dy;

    // render
    ALLEGRO_BITMAP *image;

    float radius;

    COLOR type;

};