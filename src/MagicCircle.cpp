#include "MagicCircle.h"

MagicCircle::MagicCircle(Vector2 pos, float duration, float radius, int regen_hp, ALLEGRO_COLOR color) {
    this->regen_hp = regen_hp;
    this->pos = pos;
    this->duration = duration;
    this->radius = radius;
    this->color = color;

    regen = true;
    dead = false;
    fading = false;
    al_unmap_rgb_f(color, &r, &g, &b);
    alpha = 0.6;

    timer = al_create_timer(duration / 100);
    regen_timer = al_create_timer(1);
    al_start_timer(timer);
    al_start_timer(regen_timer);
}

void MagicCircle::update() {
    int count = al_get_timer_count(timer);
    if(count <= 20) {
        alpha = 0.6 * (count * 0.05);
    } else if(count >= 80) {
        alpha = 0.6 * (1 - ((count - 80) * 0.05));
    }
    if(count >= 100) dead = true;

    if(al_get_timer_count(regen_timer)) {
        regen = true;
        al_set_timer_count(regen_timer, 0);
    } else {
        regen = false;
    }
}

void MagicCircle::render() {
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
    al_draw_filled_circle(pos.x, pos.y, radius, al_map_rgba_f(r, g, b, alpha * 0.7));
    al_draw_circle(pos.x, pos.y, radius, al_map_rgba_f(r, g, b, alpha), radius / 15);
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}

void MagicCircle::destroy() {
    al_destroy_timer(timer);
    al_destroy_timer(regen_timer);
}
