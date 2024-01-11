#pragma once

#include "Source.h"
#include "Math.h"

class Particle {

public:
    Particle(Vector2 pos, float angle, float speed, float duration, float scale, ALLEGRO_COLOR color);
    void update();
    void render();
    void destroy();
    bool dead();

private:
    Vector2 pos;
    Vector2 vel;
    
    float angle;
    float speed;
    float duration;

    float rotate_speed;
    float rotation;
    float scale;

    ALLEGRO_TIMER *timer;

    ALLEGRO_COLOR color;

    float width;
    float height;

};