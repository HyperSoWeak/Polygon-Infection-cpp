#include "Global.h"
#include "Game.h"
#include "Menu.h"
#include "GameOver.h"
#include "Source.h"
#include "State.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;

GAME_STATE game_state = GAME_STATE::MENU;
GAME_STATE prev_game_state = game_state;

Game *game;
Menu *menu;
GameOver *game_over;

State *states[3];

void run();
void init();
void update();
void render();
void handleInput();
void destroy();
void switch_state(GAME_STATE state);

int main() {
    init();
    run();
    destroy();
    return 0;
}

void run() {
    bool running = true;
    bool next_frame = true;

    al_start_timer(timer);
    while(running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        switch(event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                running = false;
                break;
            }

            case ALLEGRO_EVENT_TIMER: {
                handleInput();
                update();
                next_frame = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                int keycode = event.keyboard.keycode;
                if(keycode == ALLEGRO_KEY_ESCAPE) {
                    switch_state(GAME_STATE::GAMEOVER);
                }
                break;
            }

        }

        if(game_state == GAME_STATE::EXIT) {
            next_frame = false;
            running = false;
        }

        if(next_frame && al_is_event_queue_empty(event_queue)) {
            next_frame = false;
            render();
        }
    }
}

void init() {
    al_init();

    al_set_new_display_flags(ALLEGRO_WINDOWED);

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_acodec_addon();

    al_reserve_samples(10);

    al_set_app_name("Polygon Infection");
    al_set_display_icon(display, al_load_bitmap("image/Icon.png"));
    al_set_window_title(display, "Polygon Infection");

    al_draw_bitmap(al_load_bitmap("image/Loading.png"), 0, 0, 0);
    al_flip_display();

    Source::load_source();

    game = new Game();
    menu = new Menu();
    game_over = new GameOver(game);

    states[0] = game;
    states[1] = menu;
    states[2] = game_over;

    menu->init();
}

void update() {
    if(game_state == GAME_STATE::EXIT) return;
    states[game_state]->update();
}

void render() {
    if(game_state == GAME_STATE::EXIT) return;
    states[game_state]->render();
    al_flip_display();
}

void handleInput() {
    if(game_state == GAME_STATE::EXIT) return;
    states[game_state]->handleInput(game_state);
    switch_state(game_state);
}

void destroy() {
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    game->destroy();
    menu->destroy();
    game_over->destroy();

    Source::destroy_source();
}

void switch_state(GAME_STATE state) {
    if(state == GAME_STATE::EXIT) return;

    if(state != prev_game_state) {
        states[prev_game_state]->stop_music();
        al_rest(0.1);
        states[state]->init();
        prev_game_state = game_state = state;
    }
}