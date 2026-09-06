//Matrix.h
#pragma once
#include "Math/Vector3.h"
#include <array>
#include <cmath>

namespace Engine {
    struct Matrix4x4 {
        std::array<std::array<float, 4>, 4> m = {};

        Matrix4x4() {
            for (int i = 0; i < 4; ++i) m[i][i] = 1.0f;
        }

        static Matrix4x4 Identity() { return Matrix4x4(); }

        static Matrix4x4 Translation(const Vec3& pos) {
            Matrix4x4 mat;
            mat.m[0][3] = pos.x;
            mat.m[1][3] = pos.y;
            mat.m[2][3] = pos.z;
            return mat;
        }

        static Matrix4x4 Scale(const Vec3& scale) {
            Matrix4x4 mat;
            mat.m[0][0] = scale.x;
            mat.m[1][1] = scale.y;
            mat.m[2][2] = scale.z;
            return mat;
        }

        static Matrix4x4 RotationX(float angle) {
            Matrix4x4 mat;
            float c = std::cos(angle), s = std::sin(angle);
            mat.m[1][1] = c; mat.m[1][2] = -s;
            mat.m[2][1] = s; mat.m[2][2] = c;
            return mat;
        }

        static Matrix4x4 RotationY(float angle) {
            Matrix4x4 mat;
            float c = std::cos(angle), s = std::sin(angle);
            mat.m[0][0] = c; mat.m[0][2] = s;
            mat.m[2][0] = -s; mat.m[2][2] = c;
            return mat;
        }

        static Matrix4x4 RotationZ(float angle) {
            Matrix4x4 mat;
            float c = std::cos(angle), s = std::sin(angle);
            mat.m[0][0] = c; mat.m[0][1] = -s;
            mat.m[1][0] = s; mat.m[1][1] = c;
            return mat;
        }

        Vec3 Transform(const Vec3& point) const {
            float w = m[3][0] * point.x + m[3][1] * point.y + m[3][2] * point.z + m[3][3];
            return Vec3(
                (m[0][0] * point.x + m[0][1] * point.y + m[0][2] * point.z + m[0][3]) / w,
                (m[1][0] * point.x + m[1][1] * point.y + m[1][2] * point.z + m[1][3]) / w,
                (m[2][0] * point.x + m[2][1] * point.y + m[2][2] * point.z + m[2][3]) / w
            );
        }

        Matrix4x4 operator*(const Matrix4x4& other) const {
            Matrix4x4 result;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    result.m[i][j] = 0;
                    for (int k = 0; k < 4; ++k) {
                        result.m[i][j] += m[i][k] * other.m[k][j];
                    }
                }
            }
            return result;
        }
    };
}