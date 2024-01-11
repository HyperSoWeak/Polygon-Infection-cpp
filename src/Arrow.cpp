#include "Arrow.h"
#include <cmath>
#include <allegro5/allegro_primitives.h>
int Arrow::dmg = 1;
float Arrow::speed = 5.0f; 

Arrow::Arrow(Vector2 pos, Vector2 dir, ALLEGRO_COLOR color, int damage) {
    this->pos = pos;
    this->dir = dir;
    this->dir.normalize();
    this->color = color;
    Arrow::set_dmg(damage);
    init();
}

void Arrow::init() {
    radius = 10.0f;
}

void Arrow::update(Player& player, Tower& tower) {
    if(Math::distance(pos + dir * speed, player.getPosition()) < radius + player.radius) {
        player.gothit(dmg);
        hit = true;
    }
    else if(Math::distance(pos + dir * speed, tower.getPosition()) < radius + tower.radius) {
        tower.gothit(dmg);
        hit = true;
    }
    else pos += dir * speed;
}

void Arrow::render() {
    al_draw_line(pos.x, pos.y, pos.x + 15.0f * dir.x, pos.y + 15.0f * dir.y, color, 5.0f);
}

bool Arrow::isOffScreen() {
    return pos.x >= SCREEN_WIDTH - 400 || pos.y >= SCREEN_HEIGHT || pos.x < 0 || pos.y < 0 || hit;
}

void Arrow::set_dmg(int damage) {
    dmg = damage;
}