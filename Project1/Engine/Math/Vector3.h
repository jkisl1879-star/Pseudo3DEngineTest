//Vector3.h
#pragma once
#include <cmath>

namespace Engine {
    struct Vec3 {
        float x, y, z;

        Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

        Vec3 operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
        Vec3 operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }
        Vec3 operator*(float s) const { return { x * s, y * s, z * s }; }
        Vec3 operator/(float s) const { return { x / s, y / s, z / s }; }
        Vec3 operator-() const { return { -x, -y, -z }; }

        Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
        Vec3& operator-=(const Vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
        Vec3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
        Vec3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

        float Length() const { return std::sqrt(x * x + y * y + z * z); }
        float LengthSq() const { return x * x + y * y + z * z; }

        Vec3 Normalized() const {
            float len = Length();
            return len > 0 ? *this * (1.0f / len) : Vec3(0, 0, 0);
        }

        static float Dot(const Vec3& a, const Vec3& b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        static Vec3 Cross(const Vec3& a, const Vec3& b) {
            return {
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            };
        }
    };
}