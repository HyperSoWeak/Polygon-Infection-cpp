#include "ParticleHandler.h"
#include <algorithm>

ParticleHandler::ParticleHandler() {
    init();
}

void ParticleHandler::init() {
    group.clear();
}

void ParticleHandler::update() {
    for(auto& p : group) {
        p->update();

        if(p->dead()) {
            p->destroy();
            p = nullptr;
        }
    
    }

    group.erase(std::remove(group.begin(), group.end(), nullptr), group.end());
}

void ParticleHandler::render() {
    for(Particle *p : group) {
        p->render();
    }
}

void ParticleHandler::explode(Vector2 pos, int amount, float duration, ALLEGRO_COLOR color) {
    for(int i = 0; i < amount; i++) {
        float _speed = Math::Random(1, 5);
        float _duration = Math::Random(0.8, 1.2) * duration;
        float _scale = Math::Random(0.8, 1.2);

        float r, g, b;
        al_unmap_rgb_f(color, &r, &g, &b);
        ALLEGRO_COLOR _color = al_map_rgb_f(
            Math::clamp(r + Math::Random(-0.1, 0.1), 0, 1),
            Math::clamp(g + Math::Random(-0.1, 0.1), 0, 1),
            Math::clamp(b + Math::Random(-0.1, 0.1), 0, 1)
        );

        group.emplace_back(new Particle(pos, Math::Random(0, 2 * Math::PI), _speed, _duration, _scale, _color));
    }
}

void ParticleHandler::regenerate(Vector2 pos, int amount, float duration) {
    ALLEGRO_COLOR color = al_map_rgb_f(.2, .8, .2);

    for(int i = 0; i < amount; i++) {
        float _speed = Math::Random(0.2, 0.8);
        float _duration = Math::Random(0.8, 1.2) * duration;
        float _scale = Math::Random(0.8, 1.2);
        Vector2 _pos = Vector2(Math::Random(-10.0, 10.0) + pos.x, Math::Random(-5.0, 5.0) + pos.y);

        float r, g, b;
        al_unmap_rgb_f(color, &r, &g, &b);
        ALLEGRO_COLOR _color = al_map_rgb_f(
            Math::clamp(r + Math::Random(-0.1, 0.1), 0, 1),
            Math::clamp(g + Math::Random(-0.1, 0.1), 0, 1),
            Math::clamp(b + Math::Random(-0.1, 0.1), 0, 1)
        );

        group.emplace_back(new Particle(_pos, Math::PI * 3 / 2, _speed, _duration, _scale, _color));
    }
}