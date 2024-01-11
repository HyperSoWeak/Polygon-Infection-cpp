#include "Upgrade.h"
#include "Math.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Upgrade::Upgrade(Vector2 pos, int price, float scale, char *text) {
    this->pos = pos;
    this->text = text;
    this->price = price;
    this->scale = scale;
    init();
}

void Upgrade::init() {
    upgraded = false;
    size = Vector2(270, 130);
    font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 28, 0);
    button = new Button(pos.x + 123, pos.y + 62, 130, 55, al_map_rgb(80, 128, 159), al_map_rgb(60, 97, 120));
    level = 0;
}

void Upgrade::update(int &coins) {
    button->update();
    
    if(button->isClicked() && coins >= price) {
        upgraded = true;
        level++;
        coins -= price;
        price = (price + level * 2) * scale;
    } else {
        upgraded = false;
    }
}

void Upgrade::render() {
    al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y, 
        15, 15, al_map_rgb(117, 162, 191));
    al_draw_rounded_rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y,
        15, 15, al_map_rgb(0, 0, 0), 8);

    button->render();

    al_draw_text(font, al_map_rgb(255, 255, 255), pos.x + size.x / 2, pos.y + 10,
        ALLEGRO_ALIGN_CENTER, text);
    al_draw_textf(font, al_map_rgb(255, 255, 255), pos.x + 60, pos.y + 50,
        ALLEGRO_ALIGN_CENTER, "LV %d", level);
    al_draw_textf(font, al_map_rgb(255, 255, 255), pos.x + 60, pos.y + 80,
        ALLEGRO_ALIGN_CENTER, "$ %s", Math::formatNumber(price, 0));

    // "Upgrade" text
    al_draw_text(font, al_map_rgb(255, 255, 255), pos.x + 188, pos.y + 67,
        ALLEGRO_ALIGN_CENTER, "Upgrade");
}

bool Upgrade::isUpgraded() {
    return upgraded;
}