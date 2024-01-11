#include "Vector2.h"
#include <cmath>

const Vector2 Vector2::zero(0.0f, 0.0f);
const Vector2 Vector2::one(1.0f, 1.0f);

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    if (scalar != 0.0f) {
        return Vector2(x / scalar, y / scalar);
    } else {
        return *this;
    }
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(float scalar) {
    if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}

bool Vector2::operator==(const Vector2& other) const {
    return (x == other.x) && (y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const {
    return !((x == other.x) && (y == other.y));
}

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

void Vector2::normalize() {
    float mag = magnitude();
    if (mag != 0.0f) {
        x /= mag;
        y /= mag;
    }
}

Vector2 Vector2::normalized() const {
    Vector2 result(*this); // Create a copy of the current vector
    
    float mag = magnitude();
    if (mag != 0.0f) {
        result.x /= mag;
        result.y /= mag;
    }
    
    return result;
}