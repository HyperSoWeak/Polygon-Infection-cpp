#pragma once

#include "Math.h"
#include "Player.h"
#include "Tower.h"
#include "Bar.h"
#include "Arrow.h"
#include <allegro5/allegro.h>
#include <vector>

enum TARGET {
    PLAYER,
    TOWER
};

enum TYPE {
    SOLDIER,
    ARCHER,
    SPEEDY,
    TANK,
    SPLIT,
    SUMMONER,
    HEALER
};

class Mob {

public:
    Mob(int type, int target, Vector2 position, int wave);
    void init();
    void update(Player&,Tower&);
    void render();
    bool dead();
    void destroy();

    bool detect_enemy(Vector2,float);
    Vector2 getPosition();
    Vector2 getDirection();
    int getType();
    int getTarget();
    int getDamage();
    ALLEGRO_TIMER *summon_timer;
    ALLEGRO_TIMER *attack_timer;

    int money;
    int score;

    ALLEGRO_COLOR color;
    
    int health;
    int max_health;

private:
    Vector2 position;
    Vector2 direction;
    
    int type;
    int target;
    
    float radius;

    int damage;
    float speed;
    float attack_range;
    float attack_speed;
    
    Bar health_bar;
    
    ALLEGRO_BITMAP *image;

    int width;
    int height;

    std::vector<Arrow*> arrows;

};