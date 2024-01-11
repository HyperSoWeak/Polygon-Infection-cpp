#include "Menu.h"
#include <string>

Menu::Menu() {
    font = al_load_ttf_font("fonts/Baloo-Regular.ttf", 50, 0);

    background = al_load_bitmap("image/Menu.png");

    start = new Button(SCREEN_WIDTH / 2 - 110, 370, 220, 100, al_map_rgb(140, 140, 140), al_map_rgb(100, 100, 100));
    about = new Button(SCREEN_WIDTH / 2 - 110, 500, 220, 100, al_map_rgb(140, 140, 140), al_map_rgb(100, 100, 100));
    exit = new Button(SCREEN_WIDTH / 2 - 110, 630, 220, 100, al_map_rgb(140, 140, 140), al_map_rgb(100, 100, 100));
}

void Menu::init() {
    start->init();
    about->init();
    exit->init();

    al_play_sample(Source::menu_bgm, 0.15, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &bgm_id);
}

void Menu::update() {
    start->update();
    about->update();
    exit->update();
}

void Menu::render() {
    al_draw_bitmap(background, 0, 0, 0);
    
    start->render();
    about->render();
    exit->render();

    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 380, 1, "START");
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 510, 1, "ABOUT");
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 640, 1, "EXIT");
}

void Menu::handleInput(GAME_STATE &state) {
    if(start->isClicked()) {
        state = GAME_STATE::GAME;
    }

    if(about->isClicked()) {
        std::string url = "https://youtu.be/dQw4w9WgXcQ?si=R8zcT5FnPdKrfnj9";
        system(("start " + url).c_str());
    }

    if(exit->isClicked()) {
        state = GAME_STATE::EXIT;
    }
}

void Menu::destroy() {
    al_destroy_font(font);
    al_destroy_bitmap(background);
}

void Menu::stop_music() {
    al_stop_sample(&bgm_id);
}