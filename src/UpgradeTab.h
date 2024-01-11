#pragma once

#include "Button.h"
#include "Upgrade.h"
#include "Math.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

class UpgradeTab {

public:
    UpgradeTab(Vector2 pos, char *icon_path);
    void init();
    void update();
    void render();
    void destroy();

    bool isClicked();

private:
    Vector2 pos;

    Button *button;
    
    ALLEGRO_BITMAP *icon;

    int icon_height;

};