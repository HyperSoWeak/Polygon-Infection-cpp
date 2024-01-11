#pragma once

#include "Math.h"

class Bar {

public:
    Bar();
    Bar(float x, float y, float length, float width, float value, float maxValue);
    void init();
    void update();
    void render();
    void destroy();

    void setPosition(float x, float y);
    void setValue(float value);
    void setMaxValue(float maxValue);

private:
    Vector2 pos;
    float length;
    float width;

    float value;
    float maxValue;

    float getPercentage();

};