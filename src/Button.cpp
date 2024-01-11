#include "Button.h"
#include <allegro5/allegro_primitives.h>

Button::Button(float x, float y, float w, float h, ALLEGRO_COLOR color, ALLEGRO_COLOR hoveredColor) {
    pos = Vector2(x, y);
    size = Vector2(w, h);
    this->color = color;
    this->hoveredColor = hoveredColor;
}

void Button::init() {
    isHovered = false;
    isPressed = false;
    count = 0;
}

void Button::update() {
    al_get_mouse_state(&mouse_state);

    isHovered = checkHover();
    isPressed = isHovered && al_mouse_button_down(&mouse_state, 1);

    if(isPressed) count++;
    else count = 0;

    if(isClicked()) {
        al_play_sample(Source::button_click, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
}

void Button::render() {
    al_draw_filled_rounded_rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y, 
        10, 10, isHovered ? hoveredColor : color);
    al_draw_rounded_rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y,
        10, 10, al_map_rgb(0, 0, 0), 6);
}

void Button::destroy() {
    delete(this);
}

bool Button::checkHover() {
    Vector2 mouse_pos = Vector2(mouse_state.x, mouse_state.y);

    return mouse_pos.x > pos.x && mouse_pos.x < pos.x + size.x &&
        mouse_pos.y > pos.y && mouse_pos.y < pos.y + size.y;
}

bool Button::isClicked() {
    return count == 1;
}