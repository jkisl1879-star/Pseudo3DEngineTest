//Transform.h
#pragma once
#include "Math/Vector3.h"
#include "Math/Matrix.h"

namespace Engine {
    struct Transform {
        Vec3 position = { 0, 0, 0 };
        Vec3 rotation = { 0, 0, 0 };
        Vec3 scale = { 1, 1, 1 };
    };
}