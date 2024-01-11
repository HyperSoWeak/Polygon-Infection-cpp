#include "Game.h"
#include "Button.h"
#include "Bar.h"
#include "Global.h"
#include <allegro5/allegro_image.h>

Game::Game() {
    info_font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 36, 0);
    rest = al_create_timer(1.0f);
    particle_handler = new ParticleHandler();
}

void Game::init() {
    player.init();
    tower.init();

    Bullet::reset();

    particle_handler->init();

    wave.init();
    wave.wave_started();

    store.init();

    coins = 0;
    score = 0;

    alive = true;

    al_play_sample(Source::game_bgm, 0.15, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &bgm_id);
}

void Game::update() {
    player.update(tower, particle_handler);
    Vector2 target_pos = wave.update(player, tower, particle_handler, coins, score);
    alive = tower.update(target_pos);

    if(wave.wave_finished()) {
        al_start_timer(rest);
    }
    if(al_get_timer_count(rest) == 5) {
        al_set_timer_count(rest, 0);
        al_stop_timer(rest);
        
        wave.wave_started();
    }

    store.update(coins);
    
    particle_handler->update();
}

void Game::render() {
    al_clear_to_color(bg_color);
    
    Vector2 tower_pos = tower.getPosition();
    al_draw_circle(tower_pos.x, tower_pos.y, tower.detect_range, al_map_rgb(255, 255, 255), 1);

    player.render();
    tower.render();
    wave.render();

    store.render();
    
    al_draw_textf(info_font, al_map_rgb(255, 255, 255), 1300, 770, 1, "%s $", Math::formatNumber(coins, 2));
    al_draw_textf(info_font, al_map_rgb(255, 255, 255), 1300, 820, 1, "Score: %s", Math::formatNumber(score, 2));
    al_draw_textf(info_font, al_map_rgb(255, 255, 255), 25, 840, 0, "Wave %d", wave.get_wave());
    al_draw_textf(info_font, al_map_rgb(255, 255, 255), 1075, 840, 2, "%d Enemy Left", wave.get_current_mob_num());
    
    particle_handler->render();
}

void Game::handleInput(GAME_STATE &state) {
    if(!alive) {
        state = GAME_STATE::GAMEOVER;
    }

    player.handleInput();
    store.handleInput(tower, player);
}

void Game::destroy() {
    player.destroy();
    tower.destroy();
    wave.destroy();
}

void Game::stop_music() {
    al_stop_sample(&bgm_id);
}

int Game::get_wave_num() {
    return wave.get_wave();
}