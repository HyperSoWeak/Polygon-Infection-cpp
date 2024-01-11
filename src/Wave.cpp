#include "Wave.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

Wave::Wave() {}

void Wave::init() {
    for(auto& mob : mobs) mob->destroy();
    mobs.clear();
    for(auto& mc : mcs) mc->destroy();
    mcs.clear();

    srand(time(NULL));
    number = 0;

    spawn_timer = al_create_timer(1.5f);
}

void Wave::destroy() {
    for(auto& mob : mobs) mob->destroy();
    mobs.clear();
    for(auto& mc : mcs) mc->destroy();
    mcs.clear();
    al_destroy_timer(spawn_timer);
}

void Wave::render() {
    for(auto &mc : mcs) mc->render();

    for(auto &mob : mobs) {
        mob->render();
    }
    //al_draw_textf(Source::test_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2 - 200, 800, 1,
    //    "%d %d %d %d %d %d %d", mob_num[0], mob_num[1], mob_num[2], mob_num[3], mob_num[4], mob_num[5], mob_num[6]);
}

bool Wave::wave_finished() {
    return is_spawn_finished() && mobs.empty();
}

float Wave::get_next_spawn_duration() {
    float t = 12 * (1.0 / (1.0 + std::exp(0.15 * (float)number)));
    return Math::Random(t * 0.75, t);
}

Vector2 Wave::update(Player& player, Tower& tower, ParticleHandler *ph, int& coins, int& score) {
    if(al_get_timer_count(spawn_timer)) {
        generate_next_mobs();
        al_set_timer_speed(spawn_timer, get_next_spawn_duration());
        al_set_timer_count(spawn_timer, 0);
    }

    for(auto& mob : mobs) {
        mob->update(player, tower);

        if(mob->getType() == SUMMONER && al_get_timer_count(mob->summon_timer)) {
            al_set_timer_count(mob->summon_timer, 0);
            Vector2 direction = mob->getDirection();
            Vector2 rotate_direction = Vector2(direction.y, direction.x);

            mobs.emplace_back(new Mob(SOLDIER, mob->getTarget(), mob->getPosition() + rotate_direction * 60, number));
            mobs.emplace_back(new Mob(SOLDIER, mob->getTarget(), mob->getPosition() - rotate_direction * 60, number));
            mobs.emplace_back(new Mob(SOLDIER, mob->getTarget(), mob->getPosition() + direction * 60, number));
            mobs.emplace_back(new Mob(SOLDIER, mob->getTarget(), mob->getPosition() - direction * 60, number));
        }

        if(mob->getType() == HEALER && al_get_timer_count(mob->summon_timer)) {
            al_set_timer_count(mob->summon_timer, 0);
            mcs.emplace_back(new MagicCircle(mob->getPosition(), 4, 200, 2, al_map_rgb_f(.2, .8, .2)));
        }

        for(auto& mc : mcs) {
            if(mc->regen && Math::distance(mc->pos, mob->getPosition()) <= mc->radius) {
                mob->health = std::min(mob->max_health, mob->health + mc->regen_hp);
                ph->regenerate(mob->getPosition(), 5, 0.7);
            }
        }

        if (mob->dead()) {
            coins += mob->money;
            score += mob->score * mob->getDamage();
            
            if(mob->getType() == SPLIT) {
                Vector2 direction = mob->getDirection();
                Vector2 rotate_direction = Vector2(direction.y, direction.x);

                mobs.emplace_back(new Mob(SOLDIER, mob->getTarget(), mob->getPosition() + rotate_direction * 30, number));
                mobs.emplace_back(new Mob(SOLDIER, mob->getTarget(), mob->getPosition() - rotate_direction * 30, number));
            }

            ph->explode(mob->getPosition(), 30, 0.3, mob->color);
            al_play_sample(Source::explode_sfx, 0.2, 0.0, Math::Random(0.5f, 1.0f), ALLEGRO_PLAYMODE_ONCE, NULL);
            
            mob->destroy();
            mob = nullptr;
        }
    }
    mobs.erase(std::remove(mobs.begin(), mobs.end(), nullptr), mobs.end());

    for(auto& mc : mcs) {
        mc->update();
        if(mc->dead) {
            mc->destroy();
            mc = nullptr;
        }
    }
    mcs.erase(std::remove(mcs.begin(), mcs.end(), nullptr), mcs.end());

    for(auto& bullet : player.getBullets()) {
        if(Math::distance(bullet->getPosition(), tower.getPosition()) < tower.radius) {
            bullet->hit = 1;
        }
    }

    if(is_spawn_finished()) {
        al_stop_timer(spawn_timer);
    }

    Vector2 target_pos = Vector2::zero;
    float shortest = tower.detect_range;
    for(auto& mob : mobs) {
        if(Math::distance(mob->getPosition(), tower.getPosition()) < shortest) {
            shortest = Math::distance(mob->getPosition(), tower.getPosition());
            target_pos = mob->getPosition();
        }
    }
    return target_pos;
}

bool Wave::is_spawn_finished() {
    for(int i = 0; i < MOB_TYPE_NUM; i++) {
        if(mob_num[i] > 0) return false;
    }
    return true;
}

void Wave::wave_started() {
    ++number;
    total_mob_num = get_mob_num();

    if(number == 1)  set_mob_rand(100, 0, 0, 0, 0, 0, 0);
    if(number == 2)  set_mob_rand(60, 40, 0, 0, 0, 0, 0);
    if(number == 4)  set_mob_rand(50, 25, 10, 10, 0, 0, 0);
    if(number == 5)  set_mob_rand(50, 30, 10, 10, 10, 0, 0);
    if(number == 6)  set_mob_rand(40, 20, 10, 10, 10, 5, 0);
    if(number == 9)  set_mob_rand(30, 30, 10, 10, 10, 5, 5);
    if(number == 11) set_mob_rand(30, 30, 10, 10, 10, 10, 10);
    if(number == 13) set_mob_rand(20, 20, 20, 20, 10, 10, 10);
    if(number == 15) set_mob_rand(10, 10, 15, 15, 15, 20, 20);
    generate_mob_num_array();

    al_set_timer_count(spawn_timer, 0);
    al_start_timer(spawn_timer);
}

int Wave::get_wave() {
    return number;
}

int Wave::get_mob_num() {
    return 80 / (1 + std::exp(-0.15 * ((float)number - 10))) + 15;
}

int Wave::get_current_mob_num() {
    return mobs.size();
}

void Wave::generate_next_mobs() {
    int type = choose_type();
    if(type == last_type) type = choose_type();
    int num = Math::RandomInt(1, std::min(std::max(1, mob_num[type] / 2), max_group_num[type] * (1 + number / 3)) + 1);
    mob_num[type] -= num;

    for(int i = 0; i < num; ++i) {
        int target = Math::RandomInt(0, 2);
        float angle = Math::Random(0, 2 * Math::PI);
        Vector2 pos = Vector2(550 + sradius * cos(angle), 450 + sradius * sin(angle));

        mobs.emplace_back(new Mob(type, target, pos, number));
    }

    last_type = type;
}

void Wave::generate_mob_num_array() {
    float sum = 0;
    for(int i = 0; i < MOB_TYPE_NUM; i++) {
        mob_rate[i] = Math::Random((float)mob_rand[i] * 0.75, (float)mob_rand[i] * 1.25);
        sum += mob_rate[i];
    }
    for(int i = 0; i < MOB_TYPE_NUM; i++) {
        mob_rate[i] /= sum;
        mob_num[i] = total_mob_num * mob_rate[i];
    }
}

int Wave::choose_type() {
    float sum = 0;
    for(int i = 0; i < MOB_TYPE_NUM; i++) {
        if(mob_num[i] <= 0) {
            mob_rate[i] = 0;
        } else {
            sum += mob_rate[i];
        }
    }
    for(int i = 0; i < MOB_TYPE_NUM; i++) {
        mob_rate[i] /= sum;
    }

    float rand = Math::Random(0, 1);
    float accumulation = 0;
    for(int i = 0; i < MOB_TYPE_NUM; i++) {
        accumulation += mob_rate[i];
        if(accumulation > rand) return i;
    }
    return MOB_TYPE_NUM - 1;
}

void Wave::set_mob_rand(int a, int b, int c, int d, int e, int f, int g) {
    mob_rand[0] = a;
    mob_rand[1] = b;
    mob_rand[2] = c;
    mob_rand[3] = d;
    mob_rand[4] = e;
    mob_rand[5] = f;
    mob_rand[6] = g;
}
