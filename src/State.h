#pragma once

#include "Global.h"

class State {

public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleInput(GAME_STATE &) = 0;
    virtual void destroy() = 0;
    virtual void stop_music() = 0;

};