#include "Bullet.h"
#include "Source.h"
#include <cmath>
#include <allegro5/allegro_primitives.h>

float Bullet::dmg = 1;
float Bullet::speed = 5.0f;

void Bullet::reset() {
    Bullet::dmg = 1;
    Bullet::speed = 5.0f;
}

Bullet::Bullet(float x, float y, float angle, COLOR type) {
    this->pos = Vector2(x, y);
    this->angle = angle;
    this->type = type;
    init();
}

void Bullet::init() {
    switch(type) {
    
    case BLUE:
        image = Source::bullet_blue_image;
        break;

    case GREEN:
        image = Source::bullet_green_image;
        break;

    default: break;

    }
    radius = al_get_bitmap_height(image) / 2;
    hit = 0;
    
    dx = cos(angle) * speed;
    dy = sin(angle) * speed;

    al_play_sample(Source::shoot_sfx, 0.2, 0.0, 1.2, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Bullet::update() {
    pos+=Vector2(dx,dy);
}

void Bullet::render() {
    al_draw_bitmap(image, pos.x - radius, pos.y - radius, 0);
}

bool Bullet::isOffScreen() {
    return pos.x >= SCREEN_WIDTH - 400 || pos.y >= SCREEN_HEIGHT || pos.x < 0 || pos.y < 0 || hit;
}

Vector2 Bullet::getPosition() {
    return pos;
}

int Bullet::getDamage() {
    return dmg;
}

void Bullet::incDamage(int amount) {
    dmg += amount;
}

void Bullet::incSpeed(float amount) {
    speed += amount;
}

void Bullet::mulSpeed(float amount) {
    speed *= amount;
}