#include "Particle.h"

Particle::Particle(Vector2 pos, float angle, float speed, float duration, float scale, ALLEGRO_COLOR color) {
    this->pos = pos;
    this->angle = angle;
    this->color = color;
    this->speed = speed;
    this->duration = duration;
    this->scale = scale;
    
    rotate_speed = Math::Random(-0.1, 0.1);
    rotation = Math::Random(0, 2 * Math::PI);
    vel = Vector2(cos(angle), sin(angle)) * speed;

    timer = al_create_timer(duration / 60);
    al_start_timer(timer);

    width = al_get_bitmap_width(Source::particle_image);
    height = al_get_bitmap_height(Source::particle_image);
}

void Particle::update() {
    pos += vel;
    rotation += rotate_speed;
}

void Particle::render() {
    int count = al_get_timer_count(timer);
    if(count >= 40) {
        float r, g, b;
        al_unmap_rgb_f(color, &r, &g, &b);
        color = al_map_rgba_f(r, g, b, 1 - ((count - 40) * 0.05));
    }

    al_draw_tinted_scaled_rotated_bitmap(
        Source::particle_image, color,
        width / 2, height / 2,
        pos.x, pos.y,
        scale, scale,
        rotation, 0
    );
}

bool Particle::dead() {
    return al_get_timer_count(timer) >= 60;
}

void Particle::destroy() {
    al_destroy_timer(timer);
}