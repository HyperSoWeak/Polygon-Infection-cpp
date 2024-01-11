#pragma once

class Vector2 {

public:
    float x;
    float y;

    const static Vector2 zero;
    const static Vector2 one;

    Vector2();
    Vector2(float x, float y);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    float magnitude() const;
    void normalize();
    Vector2 normalized() const;

};