#pragma once

#include "Math.h"
#include "Global.h"
#include "Source.h"
#include <allegro5/allegro.h>

class Button {

public:
    Button(float x, float y, float w, float h, ALLEGRO_COLOR color, ALLEGRO_COLOR hoveredColor);
    void init();
    void update();
    void render();
    void destroy();

    bool checkHover();
    bool isClicked();

private:
    Vector2 pos;
    Vector2 size;

    ALLEGRO_COLOR color;
    ALLEGRO_COLOR hoveredColor;

    bool isHovered;
    bool isPressed;
    
    int count;

    ALLEGRO_MOUSE_STATE mouse_state;

};