#pragma once

#include "Button.h"
#include "Math.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

class Upgrade {

public:
    Upgrade(Vector2 pos, int price, float scale, char *text);
    void init();
    void update(int &);
    void render();
    void destroy();

    bool isUpgraded();
    int level;

private:
    Vector2 pos;
    Vector2 size;

    Button *button;
    ALLEGRO_FONT *font;

    char *text;
    int price;
    float scale;

    bool upgraded;

};