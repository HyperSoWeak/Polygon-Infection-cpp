#pragma once

#include "Math.h"
#include "Player.h"
#include "Tower.h"
#include "Global.h"
#include <allegro5/allegro.h>

class Arrow {

public:
    Arrow(Vector2 pos, Vector2 dir, ALLEGRO_COLOR color, int damage);
    void init();
    void update(Player&, Tower&);
    void render();
    bool isOffScreen();
    bool hit;
    static float speed;
    static int dmg;

private:
    Vector2 pos;
    Vector2 dir;
    ALLEGRO_COLOR color;

    static void set_dmg(int damage);
    // render
    //ALLEGRO_BITMAP *image;

    float radius;

};