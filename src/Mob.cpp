#include "Math.h"
#include "Global.h"
#include "Mob.h"
#include "Source.h"
#include <algorithm>
#include <allegro5/allegro_primitives.h>

Mob::Mob(int type, int target, Vector2 position, int wave) {
    this->type = type;
    this->target = target;
    this->position = position;

    init();

    max_health *= 1 + (float)(wave - 1) / 3;
    damage *= 1 + (float)(wave - 1) / 5;
    speed *= 1 + (float)(wave - 1) / 10;

    money *= (float)wave * 2 - 0.5;
    score *= wave;
}

void Mob::init() {
    summon_timer = nullptr;
    arrows.clear();

    switch (type) {

    case SOLDIER: {
        image = Source::soldier_image;
        radius = 25.0f;
        color = al_map_rgb(238, 230, 17);

        max_health = 3;
        damage = 3;
        speed = 1.2f;
        attack_range = 24.0f;
        attack_speed = 0.8f;
        
        money = 7;
        score = 3;
        break;
    }

    case ARCHER: {
        image = Source::archer_image;
        radius = 23.0f;
        color = al_map_rgb(232, 72, 85);

        max_health = 3;
        damage = 3;
        speed = 1.0f;
        attack_range = 200.0f;
        attack_speed = 1.0f;
        
        money = 9;
        score = 5;
        break;
    }

    case SPEEDY: {
        image = Source::speedy_image;
        radius = 20.0f;
        color = al_map_rgb(83, 119, 255);

        max_health = 2;
        damage = 2;
        speed = 2.0f;
        attack_range = 24.0f;
        attack_speed = 0.25f;
        
        money = 19;
        score = 10;
        break;
    }

    case TANK: {
        image = Source::tank_image;
        radius = 23.0f;
        color = al_map_rgb(232, 135, 30);

        max_health = 12;
        damage = 5;
        speed = 0.7f;
        attack_range = 24.0f;
        attack_speed = 1.5f;
        
        money = 24;
        score = 13;
        break;
    }

    case SPLIT: {
        image = Source::split_image;
        radius = 30.0f;
        color = al_map_rgb(238, 230, 17);

        max_health = 6;
        damage = 3;
        speed = 0.8f;
        attack_range = 24.0f;
        attack_speed = 0.8f;
        
        money = 32;
        score = 15;
        break;
    }

    case SUMMONER: {
        image = Source::summoner_image;
        radius = 32.0f;
        color = al_map_rgb(30, 206, 232);

        max_health = 8;
        damage = 1;
        speed = 0.8f;
        attack_range = 350.0f;
        attack_speed = 0.7f;
        
        money = 48;
        score = 25;

        summon_timer = al_create_timer(5.0f);
        al_start_timer(summon_timer);
        break;
    }

    case HEALER: {
        image = Source::healer_image;
        radius = 32.0f;
        color = al_map_rgb(80, 230, 60);

        max_health = 8;
        damage = 1;
        speed = 0.8f;
        attack_range = 300.0f;
        attack_speed = 0.7f;
        
        money = 40;
        score = 25;

        summon_timer = al_create_timer(6.0f);
        al_start_timer(summon_timer);
        break;
    }

    }

    width = al_get_bitmap_width(image);
    height = al_get_bitmap_height(image);

    health = max_health;

    attack_timer = al_create_timer(attack_speed);
    al_start_timer(attack_timer);

    health_bar = Bar(position.x - 40, position.y + 40, 80, 8, health, max_health);
}

void Mob::update(Player& player,Tower& tower) {
    switch (target) {
        case TOWER:
            if(detect_enemy(tower.getPosition(), tower.radius)) {
                direction = tower.getPosition() - position;
                direction.normalize();
                if(al_get_timer_count(attack_timer)) {
                    if(type != ARCHER && type != SUMMONER && type != HEALER) tower.gothit(damage);
                    else {
                        arrows.emplace_back(new Arrow(position, direction, color, damage));
                    }
                    al_stop_timer(attack_timer);
                    al_set_timer_count(attack_timer, 0);
                    al_start_timer(attack_timer);
                }
            } else if(player.alive && detect_enemy(player.getPosition(), player.radius)) {
                direction = player.getPosition() - position;
                direction.normalize();
                if(al_get_timer_count(attack_timer)) {
                    if(type != ARCHER && type != SUMMONER && type != HEALER) player.gothit(damage);
                    else {
                        arrows.emplace_back(new Arrow(position, direction, color, damage));
                    }
                    al_stop_timer(attack_timer);
                    al_set_timer_count(attack_timer, 0);
                    al_start_timer(attack_timer);
                }
            } else {
                direction = tower.getPosition() - position;
                direction.normalize();
                position += direction * speed;
            }
            break;
        case PLAYER:
            if(player.alive && detect_enemy(player.getPosition(), player.radius)) {
                direction = player.getPosition() - position;
                direction.normalize();
                if(al_get_timer_count(attack_timer)) {
                    if(type != ARCHER && type != SUMMONER && type != HEALER) player.gothit(damage);
                    else {
                        arrows.emplace_back(new Arrow(position, direction, color, damage));
                    }
                    al_stop_timer(attack_timer);
                    al_set_timer_count(attack_timer, 0);
                    al_start_timer(attack_timer);
                }
            } else if(detect_enemy(tower.getPosition(), tower.radius)) {
                direction = tower.getPosition() - position;
                direction.normalize();
                if(al_get_timer_count(attack_timer)) {
                    if(type != ARCHER && type != SUMMONER && type != HEALER) tower.gothit(damage);
                    else {
                        arrows.emplace_back(new Arrow(position, direction, color, damage));
                    }
                    al_stop_timer(attack_timer);
                    al_set_timer_count(attack_timer, 0);
                    al_start_timer(attack_timer);
                }
            } else {
                if(player.alive) direction = player.getPosition() - position;
                else direction = tower.getPosition() - position;
                direction.normalize();
                position += direction * speed;
            }
            break;
        default:
            break;
    }

    for(auto& bullet : player.getBullets()) {
        if(Math::distance(bullet->getPosition(), position) < radius) {
            health -= bullet->getDamage();
            bullet->hit = 1;
        }
    }
    for(auto& bullet : tower.getBullets()) {
        if(Math::distance(bullet->getPosition(), position) < radius) {
            health -= bullet->getDamage();
            bullet->hit = 1;
        }
    }
    for(auto& arrow : arrows) {
        arrow->update(player, tower);
        if(arrow->isOffScreen()) {
            arrow = nullptr;
        }
    }
    arrows.erase(std::remove(arrows.begin(), arrows.end(), nullptr), arrows.end());

    health_bar.setPosition(position.x - 40, position.y + 40);
    health_bar.setValue(health);
}

void Mob::render() {
    for(auto& arrow : arrows) {
        arrow->render();
    }
    
    al_draw_rotated_bitmap(image, width / 2, height / 2,
        position.x, position.y, Math::radBtwPoints(Vector2::zero, direction), 0);

    //health_bar.render();
}

bool Mob::dead() {
    return health <= 0;
}

bool Mob::detect_enemy(Vector2 target, float target_radius) {
    if(Math::distance(position, target) < (target_radius + attack_range)) return true;
    return false;
}

Vector2 Mob::getPosition() {
    return position;
}

Vector2 Mob::getDirection() {
    return direction;
}

int Mob::getType() {
    return type;
}

int Mob::getTarget() {
    return target;
}

int Mob::getDamage() {
    return damage;
}

void Mob::destroy() {
    if(summon_timer) al_destroy_timer(summon_timer);
    arrows.clear();
    al_destroy_timer(attack_timer);
}