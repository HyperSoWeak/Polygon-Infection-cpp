#pragma once

#include <cmath>
#include "Vector2.h"

class Math {

public:
    static const double PI;
    static const double EXP;

    static float dot(const Vector2& v1, const Vector2& v2);
    static float cross(const Vector2& v1, const Vector2& v2);

    static float lerp(float start, float end, float t);
    static float clamp(float value, float min, float max);
    
    static float deg2Rad(float degrees);
    static float rad2Deg(float radians);

    static float radBtwPoints(const Vector2& v1, const Vector2& v2);
    static float distance(const Vector2& v1, const Vector2& v2);

    static int RandomInt(const int min, const int max);
    static float Random(const float min, const float max);

    static char *formatNumber(int number, int digit);
};