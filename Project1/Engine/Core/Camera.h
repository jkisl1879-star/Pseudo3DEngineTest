//Camera.h
#pragma once
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include <cmath>

namespace Engine {
    class Camera {
    public:
        Vec3 position = { 0, 0, -8 };
        Vec3 rotation = { 0, 0, 0 };
        float fov = 60.0f;
        float nearPlane = 0.1f;

        bool Project(const Vec3& point, Vec2& screenPos, int screenWidth, int screenHeight) const {
            Vec3 relative = point - position;

            // ★ ПОВОРОТ ПО Y (YAW) ★
            float cosY = std::cos(-rotation.y);
            float sinY = std::sin(-rotation.y);
            float x = relative.x * cosY - relative.z * sinY;
            float z = relative.x * sinY + relative.z * cosY;

            // ★ ПОВОРОТ ПО X (PITCH) — БЕЗ ОГРАНИЧЕНИЙ ★
            float cosX = std::cos(-rotation.x);
            float sinX = std::sin(-rotation.x);
            float y = relative.y * cosX - z * sinX;
            z = relative.y * sinX + z * cosX;

            if (z <= nearPlane) return false;

            float aspect = static_cast<float>(screenWidth) / screenHeight;
            float fovRad = fov * 3.14159f / 180.0f;
            float scale = 1.0f / std::tan(fovRad / 2.0f);

            screenPos.x = (x / z) * scale * aspect * screenHeight / 2.0f + screenWidth / 2.0f;
            screenPos.y = -(y / z) * scale * screenHeight / 2.0f + screenHeight / 2.0f;

            return true;
        }

        Vec3 GetForward() const {
            float cy = std::cos(rotation.y);
            float sy = std::sin(rotation.y);
            float cp = std::cos(rotation.x);
            float sp = std::sin(rotation.x);

            return {
                -sy * cp,
                sp,
                -cy * cp
            };
        }

        Vec3 GetRight() const {
            float cy = std::cos(rotation.y);
            float sy = std::sin(rotation.y);

            return {
                cy,
                0,
                -sy
            };
        }

        Vec3 GetUp() const {
            Vec3 forward = GetForward();
            Vec3 right = GetRight();
            return Vec3::Cross(right, forward).Normalized();
        }
    };
}