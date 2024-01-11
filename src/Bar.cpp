#include "Bar.h"
#include <allegro5/allegro_primitives.h>

Bar::Bar() {}

Bar::Bar(float x, float y, float length, float width, float value, float maxValue) : pos(x, y), length(length), width(width), value(value), maxValue(maxValue) {}

void Bar::init() {

}

void Bar::update() {

}

void Bar::render() {
    al_draw_rounded_rectangle(pos.x, pos.y, pos.x + length, pos.y + width,
        width / 2, width / 2, al_map_rgb(200, 200, 200), width / 2);
    al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x + length, pos.y + width,
        width / 2, width / 2, al_map_rgb(100, 100, 100));
    
    float p = getPercentage();

    ALLEGRO_COLOR color;
    if(p <= 0.5) color = al_map_rgb(160, 20 + 140 * p * 2, 0);
    else color = al_map_rgb(20 + 140 * (1.0f - p) * 2, 160, 0);

    if(p != 0) {
        al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x + length * getPercentage(), pos.y + width,
            width / 2, width / 2, color);
    }
}

float Bar::getPercentage() {
    float p = value / maxValue;
    if(p < 0.05) return 0;
    else if(p > 1) return 1;
    else return p;
}

void Bar::destroy() {
    
}

void Bar::setPosition(float x, float y) {
    pos = Vector2(x, y);
}

void Bar::setValue(float value) {
    this->value = value;
}

void Bar::setMaxValue(float maxValue) {
    this->maxValue = maxValue;
}