//Collision.h
#pragma once
#include "Math/Vector2.h"

namespace Engine {
    struct Rect {
        Vec2 position;
        Vec2 size;

        Rect(float x = 0, float y = 0, float w = 1, float h = 1)
            : position(x, y), size(w, h) {
        }

        bool Intersects(const Rect& other) const {
            return position.x < other.position.x + other.size.x &&
                position.x + size.x > other.position.x &&
                position.y < other.position.y + other.size.y &&
                position.y + size.y > other.position.y;
        }

        bool Contains(const Vec2& point) const {
            return point.x >= position.x && point.x <= position.x + size.x &&
                point.y >= position.y && point.y <= position.y + size.y;
        }
    };
}