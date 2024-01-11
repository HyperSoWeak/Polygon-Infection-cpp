#pragma once

#include "Source.h"
#include "Math.h"
#include "Global.h"

class MagicCircle {

public:
    MagicCircle(Vector2 pos, float duration, float radius, int regen_hp, ALLEGRO_COLOR color);
    void update();
    void render();
    void destroy();

    int regen_hp;

    bool regen;
    bool dead;

    Vector2 pos;
    float radius;

private:
    float duration;

    ALLEGRO_TIMER *timer;
    ALLEGRO_TIMER *regen_timer;
    ALLEGRO_COLOR color;

    float r, g, b;
    float alpha;

    bool fading;

};