#include "Math.h"
#include "Global.h"
#include "Player.h"
#include "Source.h"
#include <algorithm>
#include <allegro5/allegro_primitives.h>

Player::Player() {}

void Player::init() {
    bullets.clear();
    font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 40, 0);
    
    pos = Vector2(400, SCREEN_HEIGHT / 2);

    speed = 3.0f;
    fire_rate = 2.0f;
    health = max_health = 20;
    regeneration = 0.9;
    dmg = 1;
    alive = true;
    left = right = up = down = firing = false;
    health_bar = Bar(pos.x - 40, pos.y + 40, 80, 8, health, max_health);

    bullet_timer = al_create_timer(1.0 / fire_rate);
    regen_timer = al_create_timer(1.0);
    respawn_timer = al_create_timer(1.0f);

    al_start_timer(regen_timer);

    base_bitmap = Source::player_base_image;
    barrel_bitmap = Source::player_barrel_image;

    radius = al_get_bitmap_height(base_bitmap) / 2;
    barrel_height = al_get_bitmap_height(barrel_bitmap);
    barrel_width = al_get_bitmap_width(barrel_bitmap);

    al_start_timer(bullet_timer);
}

void Player::update(Tower& tower, ParticleHandler *ph) {
    if(al_get_timer_count(respawn_timer) == 10) {
        alive = true;
        health = max_health;
        //respawn_effect
        al_stop_timer(respawn_timer);
        al_set_timer_count(respawn_timer, 0);
        al_play_sample(Source::respawn_sfx, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        ph->regenerate(pos, 20, 1.5);
    }
    facing = Math::radBtwPoints(pos, mouse_pos);
    if(firing && al_get_timer_count(bullet_timer) > 0) {
        fireBullet();
        al_stop_timer(bullet_timer);
        al_set_timer_count(bullet_timer, 0);
        al_start_timer(bullet_timer);
    }

    for (auto& bullet : bullets) {
        bullet->update();

        if (bullet->isOffScreen()) {
            bullet = nullptr;
        }
    }
    bullets.erase(std::remove(bullets.begin(), bullets.end(), nullptr), bullets.end());
    
    if(!alive) return;

    direction = Vector2::zero;

    if(left) direction.x--;
    if(right) direction.x++;
    if(up) direction.y--;
    if(down) direction.y++;

    if(direction.x != 0) {
        vel.x += 0.3 * direction.x;
        vel.x = Math::clamp(vel.x, -speed, speed);
    } else {
        vel.x *= 0.95;
    }

    if(direction.y != 0) {
        vel.y += 0.3 * direction.y;
        vel.y = Math::clamp(vel.y, -speed, speed);
    } else {
        vel.y *= 0.95;
    }

    direction.normalize();
    if(Math::distance(pos + vel, tower.getPosition()) > (radius + tower.radius)) pos += vel;
    
    pos.x = Math::clamp(pos.x, 0, SCREEN_WIDTH - 400);
    pos.y = Math::clamp(pos.y, 0, SCREEN_HEIGHT);

    if(al_get_timer_count(regen_timer) >= 5) {
        al_set_timer_count(regen_timer, 4);
        health += regeneration;
        health = std::min(health, max_health);
    }

    health_bar.setPosition(pos.x - 40, pos.y + 40);
    health_bar.setValue(health);
    
}

void Player::render() {
    for(auto &bullet : bullets) {
        bullet->render();
    }
    if(!alive) {
        al_draw_textf(font, al_map_rgb(255, 255, 255), (SCREEN_WIDTH - 400) / 2, 100, ALLEGRO_ALIGN_CENTER, "Player revived in %d seconds", 10 - al_get_timer_count(respawn_timer));
        return;
    }
    al_draw_rotated_bitmap(barrel_bitmap, 0, barrel_height / 2, pos.x, pos.y, facing, 0);
    al_draw_bitmap(base_bitmap, pos.x - radius, pos.y - radius, 0);

    health_bar.render();
}

void Player::handleInput() {
    al_get_keyboard_state(&key_state);

    left  = al_key_down(&key_state, ALLEGRO_KEY_A) || al_key_down(&key_state, ALLEGRO_KEY_LEFT);
    right = al_key_down(&key_state, ALLEGRO_KEY_D) || al_key_down(&key_state, ALLEGRO_KEY_RIGHT);
    up    = al_key_down(&key_state, ALLEGRO_KEY_W) || al_key_down(&key_state, ALLEGRO_KEY_UP);
    down  = al_key_down(&key_state, ALLEGRO_KEY_S) || al_key_down(&key_state, ALLEGRO_KEY_DOWN);
    firing = al_key_down(&key_state, ALLEGRO_KEY_SPACE);

    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    mouse_pos.x = static_cast<float>(mouse_state.x);
    mouse_pos.y = static_cast<float>(mouse_state.y);
}

void Player::destroy() {
    for(auto &bullet : bullets) {
        delete bullet;
    }

    bullets.clear();

    al_destroy_timer(bullet_timer);
    al_destroy_timer(regen_timer);
    al_destroy_timer(respawn_timer);
    al_destroy_font(font);
}

void Player::fireBullet() {
    if(!alive) return;
    bullets.emplace_back(new Bullet(
        pos.x + cos(facing) * (barrel_width - 10), pos.y + sin(facing) * (barrel_width - 10),
        facing, BLUE));
}

Vector2 Player::getPosition() {
    return pos;
}

std::vector<Bullet*> Player::getBullets() {
    return bullets;
}

void Player::gothit(int damage) {
    health -= damage;
    if(health < 0) {
        alive = false;
        //dead_effect
        al_start_timer(respawn_timer);
    }
    health = std::max(health ,0);
    al_set_timer_count(regen_timer, 0);
}

void Player::incMaxHealth(int amount) {
    max_health += amount;
    health_bar.setMaxValue(max_health);
}

void Player::incRegen(int amount) {
    regeneration += amount;
}

void Player::incFireRate(float amount) {
    fire_rate += amount;
    al_set_timer_speed(bullet_timer, (double)1.0 / fire_rate);
}

void Player::incSpeed(float amount) {
    speed += amount;
}