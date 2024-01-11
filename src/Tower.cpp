#include "Tower.h"
#include "Global.h"
#include <algorithm>
#include <allegro5/allegro_primitives.h>

Tower::Tower() {}

void Tower::init() {
    pos = Vector2(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2);
    bar_offset = Vector2(-80, 82);
    
    fire_rate = 1.0f;
    damage = 1;

    max_health = 50;
    health = max_health;
    regeneration = 0.9;
    health_bar = Bar(pos.x + bar_offset.x, pos.y + bar_offset.y, 160, 12, health, max_health);

    event_queue = al_create_event_queue();
    bullet_timer = al_create_timer(1.0 / fire_rate);
    regen_timer = al_create_timer(1.0);

    al_register_event_source(event_queue, al_get_timer_event_source(bullet_timer));

    al_start_timer(bullet_timer);
    al_start_timer(regen_timer);

    base_bitmap = al_load_bitmap("image/tower/Base.png");
    cannon_bitmap = al_load_bitmap("image/tower/Cannon.png");
    barrel_bitmap = al_load_bitmap("image/tower/Barrel.png");

    base_width = al_get_bitmap_width(base_bitmap);
    base_height = al_get_bitmap_height(base_bitmap);
    barrel_height = al_get_bitmap_height(barrel_bitmap);
    barrel_width = al_get_bitmap_width(barrel_bitmap);
    cannon_radius = al_get_bitmap_height(cannon_bitmap) / 2;
    radius = base_height / 2;
    detect_range = 200.0f;

    facing_angle = 0.0f;
    
    bullets.clear();
}

bool Tower::update(Vector2 target_pos) {
    ALLEGRO_EVENT event;
    if(al_get_next_event(event_queue, &event)) {
        if(target_pos != Vector2::zero) fireBullet(target_pos);
    }

    if(al_get_timer_count(regen_timer) >= 5) {
        al_set_timer_count(regen_timer, 4);
        health += regeneration;
        health = std::min(health, max_health);
    }

    health_bar.setPosition(pos.x + bar_offset.x, pos.y + bar_offset.y);
    health_bar.setValue(health);

    for(auto& bullet : bullets) {
        bullet->update();

        if (bullet->isOffScreen()) {
            bullet = nullptr;
        }
    }

    bullets.erase(std::remove(bullets.begin(), bullets.end(), nullptr), bullets.end());
    return health > 0;
}

void Tower::render() {
    al_draw_bitmap(base_bitmap, pos.x - base_width / 2, pos.y - base_height / 2, 0);

    for(auto &bullet : bullets) {
        bullet->render();
    }
    
    al_draw_rotated_bitmap(barrel_bitmap, 0, barrel_height / 2, pos.x, pos.y, facing_angle, 0);
    al_draw_bitmap(cannon_bitmap, pos.x - cannon_radius, pos.y - cannon_radius, 0);

    health_bar.render();
}

void Tower::handleInput() {}

void Tower::destroy() {
    for(auto &bullet : bullets) {
        delete bullet;
    }

    bullets.clear();

    al_destroy_event_queue(event_queue);
    al_destroy_timer(bullet_timer);
}

void Tower::fireBullet(Vector2 target_pos) {
    facing_angle = Math::radBtwPoints(pos, target_pos);
    bullets.emplace_back(new Bullet(pos.x + cos(facing_angle) * (barrel_width - 10), pos.y + sin(facing_angle) * (barrel_width - 10),
        Math::radBtwPoints(pos, target_pos), GREEN));
}

Vector2 Tower::getPosition() {
    return pos;
}

std::vector<Bullet*> Tower::getBullets() {
    return bullets;
}

void Tower::gothit(int damage) {
    health -= damage;
    al_set_timer_count(regen_timer, 0);
}

void Tower::incMaxHealth(int amount) {
    max_health += amount;
    health_bar.setMaxValue(max_health);
}

void Tower::incRegen(int amount) {
    regeneration += amount;
}

void Tower::incFireRate(float amount) {
    fire_rate += amount;
    al_set_timer_speed(bullet_timer, (double)1.0 / fire_rate);
}

void Tower::incRange(float amount) {
    detect_range += amount;
}