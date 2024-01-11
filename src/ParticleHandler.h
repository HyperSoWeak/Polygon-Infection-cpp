#pragma once

#include "Particle.h"
#include <vector>

class ParticleHandler {

public:
    ParticleHandler();
    void init();
    void update();
    void render();
    void explode(Vector2 pos, int amount, float duration, ALLEGRO_COLOR color);
    void regenerate(Vector2 pos, int amount, float duration);

private:
    std::vector<Particle*> group;

};