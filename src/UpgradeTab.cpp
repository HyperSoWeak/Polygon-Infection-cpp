#include "UpgradeTab.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

UpgradeTab::UpgradeTab(Vector2 pos, char *icon_path) {
    this->pos = pos;
    this->icon = al_load_bitmap(icon_path);
    init();
}

void UpgradeTab::init() {
    button = new Button(pos.x, pos.y, 125, 100, al_map_rgb(173, 173, 173), al_map_rgb(160, 160, 160));
    icon_height = al_get_bitmap_height(icon);
}

void UpgradeTab::update() {
    button->update();
}

void UpgradeTab::render() {
    button->render();
    
    al_draw_bitmap(icon, pos.x + 10, pos.y + 50 - (float)icon_height / 2, 0);
}

bool UpgradeTab::isClicked() {
    return button->isClicked();
}