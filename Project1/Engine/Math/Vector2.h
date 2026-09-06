//Vector2.h
#pragma once
#include <cmath>

namespace Engine {
    struct Vec2 {
        float x, y;

        Vec2(float x = 0, float y = 0) : x(x), y(y) {}

        Vec2 operator+(const Vec2& other) const { return { x + other.x, y + other.y }; }
        Vec2 operator-(const Vec2& other) const { return { x - other.x, y - other.y }; }
        Vec2 operator*(float s) const { return { x * s, y * s }; }
        Vec2 operator/(float s) const { return { x / s, y / s }; }
        Vec2 operator-() const { return { -x, -y }; }

        Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
        Vec2& operator-=(const Vec2& other) { x -= other.x; y -= other.y; return *this; }
        Vec2& operator*=(float s) { x *= s; y *= s; return *this; }
        Vec2& operator/=(float s) { x /= s; y /= s; return *this; }

        float Length() const { return std::sqrt(x * x + y * y); }
        float LengthSq() const { return x * x + y * y; }

        Vec2 Normalized() const {
            float len = Length();
            return len > 0 ? *this * (1.0f / len) : Vec2(0, 0);
        }
    };
}