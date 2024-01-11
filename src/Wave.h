#pragma once

#include "ParticleHandler.h"
#include "MagicCircle.h"
#include "Math.h"
#include "Mob.h"
#include <allegro5/allegro.h>
#include <vector>

#define sradius 700

class Wave {

public:
    Wave();
    void init();
    void destroy();
    void render();
    Vector2 update(Player&, Tower&, ParticleHandler*, int&, int&);

    bool wave_finished();
    void wave_started();
    int get_wave();
    int get_current_mob_num();

private:
    int number;
    int total_mob_num;

    int get_mob_num();
    
    std::vector<Mob*> mobs;

    ALLEGRO_TIMER *spawn_timer;

    void generate_next_mobs();
    void generate_mob_num_array();
    int choose_type();
    bool is_spawn_finished();

    float get_next_spawn_duration();

    // SOLDIER, ARCHER, SPEEDY, TANK, SPLIT, SUMMONER, HEALER
    int max_group_num[MOB_TYPE_NUM] = {3, 3, 2, 2, 2, 1, 1};
    int mob_rand[MOB_TYPE_NUM];
    int mob_num[MOB_TYPE_NUM];
    float mob_rate[MOB_TYPE_NUM];

    int last_type;

    std::vector<MagicCircle*> mcs;

    void set_mob_rand(int, int, int, int, int, int, int);

};