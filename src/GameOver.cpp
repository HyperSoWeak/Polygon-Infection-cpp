#include "GameOver.h"

GameOver::GameOver(Game *game) {
    this->game = game;

    title_font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 110, 0);
    info_font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 40, 0);

    fade_timer = al_create_timer(1.0);

    restart = new Button(SCREEN_WIDTH / 2 - 100, 510, 200, 80, al_map_rgb(140, 140, 140), al_map_rgb(100, 100, 100));
    menu = new Button(SCREEN_WIDTH / 2 - 100, 620, 200, 80, al_map_rgb(140, 140, 140), al_map_rgb(100, 100, 100));
}

void GameOver::init() {
    fading = true;
    restart->init();

    al_stop_timer(fade_timer);
    al_set_timer_count(fade_timer, 0);
    al_start_timer(fade_timer);

    al_play_sample(Source::gameover_music, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void GameOver::update() {
    if(al_get_timer_count(fade_timer)) {
        fading = false;
        al_stop_timer(fade_timer);
    }

    if(!fading) {
        restart->update();
        menu->update();
    }
}

void GameOver::render() {
    if(fading) {
        al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba_f(0.1, 0.0, 0.0, 0.005));
    } else {
        restart->render();
        menu->render();

        al_draw_text(info_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 520, 1, "RESTART");
        al_draw_text(info_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 630, 1, "MENU");

        al_draw_text(title_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 140, 1, "Game Over");
        al_draw_textf(info_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 300, 1, "Your Score: %d", game->score);
        al_draw_textf(info_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 370, 1, "You survived %d waves!", game->get_wave_num() - 1);
    }
}

void GameOver::handleInput(GAME_STATE &state) {
    if(!fading) {
        if(restart->isClicked()) {
            state = GAME_STATE::GAME;
        } else if(menu->isClicked()) {
            state = GAME_STATE::MENU;
            al_rest(0.1f);
        }
    }
}

void GameOver::destroy() {
    al_destroy_font(title_font);
    al_destroy_timer(fade_timer);
}

void GameOver::stop_music() {
    
}