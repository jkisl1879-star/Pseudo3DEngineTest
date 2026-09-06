#pragma once
#include "Graphics/ConsoleBuffer.h"
#include "Core/Camera.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include <vector>
#include <cmath>

namespace Engine {

    struct RaycastResult {
        bool hit = false;
        float distance = 0.0f;
        int side = 0;
        int mapX = 0;
        int mapY = 0;
        float wallX = 0.0f;
    };

    class Raycaster {
    private:
        int mapWidth = 24;
        int mapHeight = 24;
        std::vector<std::vector<int>> map;

        bool canFly = true;
        float playerRadius = 0.3f;
        float fov = 0.66f;

        WORD skyColor = 0x0009;
        WORD groundColor = 0x0002;
        WORD wallColor1 = 0x000E;
        WORD wallColor2 = 0x0006;
        wchar_t wallChar = L'#';

        void InitMap() {
            map = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
                {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
                {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
            };
        }

        bool IsWall(float x, float y) const {
            int mx = (int)std::floor(x);
            int my = (int)std::floor(y);
            if (mx < 0 || mx >= mapWidth || my < 0 || my >= mapHeight) return true;
            return map[my][mx] == 1;
        }

        RaycastResult CastRay(float posX, float posY, float rayDirX, float rayDirY) const {
            RaycastResult result;

            int mapX = (int)posX;
            int mapY = (int)posY;

            float deltaDistX = std::abs(1.0f / rayDirX);
            float deltaDistY = std::abs(1.0f / rayDirY);

            float sideDistX, sideDistY;
            int stepX, stepY;

            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else {
                stepX = 1;
                sideDistX = (mapX + 1.0f - posX) * deltaDistX;
            }

            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else {
                stepY = 1;
                sideDistY = (mapY + 1.0f - posY) * deltaDistY;
            }

            int hit = 0;
            int side = 0;

            for (int i = 0; i < 100; ++i) {
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }

                if (mapX < 0 || mapX >= mapWidth || mapY < 0 || mapY >= mapHeight) break;

                if (map[mapY][mapX] == 1) {
                    hit = 1;
                    break;
                }
            }

            if (!hit) return result;

            float perpDist;
            float wallX = 0.0f;

            if (side == 0) {
                perpDist = (mapX - posX + (1 - stepX) / 2.0f) / rayDirX;
                wallX = posY + perpDist * rayDirY;
            }
            else {
                perpDist = (mapY - posY + (1 - stepY) / 2.0f) / rayDirY;
                wallX = posX + perpDist * rayDirX;
            }

            if (perpDist < 0.01f) perpDist = 0.01f;

            result.hit = true;
            result.distance = perpDist;
            result.side = side;
            result.mapX = mapX;
            result.mapY = mapY;
            result.wallX = wallX - std::floor(wallX);

            return result;
        }

        int CalculateWallHeight(float distance, int screenH) const {
            int height = (int)(screenH / distance);
            if (height > screenH) height = screenH;
            return height;
        }

        void CalculateWallPosition(int wallHeight, int horizonY, int screenH, int& drawStart, int& drawEnd) const {
            drawStart = -wallHeight / 2 + horizonY;
            if (drawStart < 0) drawStart = 0;
            drawEnd = wallHeight / 2 + horizonY;
            if (drawEnd >= screenH) drawEnd = screenH - 1;
        }

        void GetCameraVectors(const Camera& camera, float& dirX, float& dirY, float& planeX, float& planeY) const {
            dirX = -std::sin(camera.rotation.y);
            dirY = -std::cos(camera.rotation.y);
            planeX = std::cos(camera.rotation.y) * fov;
            planeY = -std::sin(camera.rotation.y) * fov;
        }

        int CalculateHorizon(int screenH, float pitch) const {
            return (int)(screenH / 2.0f + pitch * 30.0f);
        }

    public:
        Raycaster() {
            InitMap();
        }

        void SetColors(WORD sky, WORD ground, WORD wall1, WORD wall2) {
            skyColor = sky;
            groundColor = ground;
            wallColor1 = wall1;
            wallColor2 = wall2;
        }

        void SetWallChar(wchar_t ch) {
            wallChar = ch;
        }

        void SetFOV(float f) {
            fov = f;
        }

        void SetFlyMode(bool fly) {
            canFly = fly;
        }

        bool GetFlyMode() const {
            return canFly;
        }

        void MoveCamera(Camera& camera, const Vec3& delta) {
            float newX = camera.position.x + delta.x;
            if (!IsWall(newX, camera.position.z)) {
                camera.position.x = newX;
            }

            float newZ = camera.position.z + delta.z;
            if (!IsWall(camera.position.x, newZ)) {
                camera.position.z = newZ;
            }

            if (canFly) {
                camera.position.y += delta.y;
            }
        }

        void GetMap(int& w, int& h, std::vector<std::vector<int>>& outMap) const {
            w = mapWidth;
            h = mapHeight;
            outMap = map;
        }

        void Render(ConsoleBuffer& buffer, const Camera& camera, float deltaTime = 0.0f) {
            int screenW = buffer.GetWidth();
            int screenH = buffer.GetHeight();

            float posX = camera.position.x;
            float posY = camera.position.z;

            float dirX, dirY, planeX, planeY;
            GetCameraVectors(camera, dirX, dirY, planeX, planeY);

            int horizonY = CalculateHorizon(screenH, camera.rotation.x);

            // ===== НЕБО (без std::min) =====
            int maxSkyY = horizonY;
            if (maxSkyY > screenH) maxSkyY = screenH;
            for (int y = 0; y < maxSkyY; ++y) {
                for (int x = 0; x < screenW; ++x) {
                    buffer.SetPixel(x, y, L' ', skyColor | (0x0001 << 4));
                }
            }

            // ===== ПОЛ (без std::max) =====
            int startGroundY = horizonY;
            if (startGroundY < 0) startGroundY = 0;
            for (int y = startGroundY; y < screenH; ++y) {
                for (int x = 0; x < screenW; ++x) {
                    buffer.SetPixel(x, y, L' ', groundColor | (0x0002 << 4));
                }
            }

            // ===== СТЕНЫ =====
            for (int x = 0; x < screenW; ++x) {
                float cameraX = 2.0f * x / screenW - 1.0f;
                float rayDirX = dirX + planeX * cameraX;
                float rayDirY = dirY + planeY * cameraX;

                RaycastResult result = CastRay(posX, posY, rayDirX, rayDirY);
                if (!result.hit) continue;

                int wallHeight = CalculateWallHeight(result.distance, screenH);
                int drawStart, drawEnd;
                CalculateWallPosition(wallHeight, horizonY, screenH, drawStart, drawEnd);

                WORD color = (result.side == 0) ? wallColor1 : wallColor2;

                for (int y = drawStart; y < drawEnd; ++y) {
                    buffer.SetPixel(x, y, wallChar, color);
                }
            }
        }
    };
}