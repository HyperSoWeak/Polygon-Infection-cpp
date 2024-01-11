#include "Math.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>

const double Math::PI = 3.1416;
const double Math::EXP = 2.7183;

float Math::dot(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float Math::cross(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

float Math::lerp(float start, float end, float t) {
    return start + t * (end - start);
}

float Math::clamp(float value, float min, float max) {
    return std::fmax(min, std::fmin(value, max));
}

float Math::deg2Rad(float degrees) {
    return degrees * (PI / 180.0f);
}

float Math::rad2Deg(float radians) {
    return radians * (180.0f / PI);
}

float Math::radBtwPoints(const Vector2& v1, const Vector2& v2) {
    return std::atan2(v2.y - v1.y, v2.x - v1.x);
}

float Math::distance(const Vector2& v1, const Vector2& v2) {
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

int Math::RandomInt(const int min, const int max) {
    return rand() % (max - min) + min;
}

float Math::Random(const float min, const float max) {
    return (float) (max - min) * rand() / RAND_MAX + min;
}

char *Math::formatNumber(int number, int digit) {
    const char *suffixes[] = {"", "k", "m", "b", "t"};
    int suffixIndex = 0;
    int num = number;

    while (num >= 1000 && suffixIndex < sizeof(suffixes) / sizeof(suffixes[0]) - 1) {
        num /= 1000;
        suffixIndex++;
    }

    char *result = new char[20];

    if (suffixIndex == 0) {
        std::sprintf(result, "%d", number);
    } else {
        std::sprintf(result, "%.*f%s", digit, static_cast<float>(number) / pow(1000, suffixIndex), suffixes[suffixIndex]);
    }

    return result;
}