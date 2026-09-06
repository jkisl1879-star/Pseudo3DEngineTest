#include <iostream>
#include "Core/Engine.h"
#include "Scene/Raycaster.h"
#include "Core/Camera.h"
#include <memory>
#include <cmath>
#include <windows.h>

using namespace Engine;

static void SetFullscreen() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
    SetWindowLong(hwnd, GWL_STYLE,
        GetWindowLong(hwnd, GWL_STYLE) & ~WS_VSCROLL & ~WS_HSCROLL);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD maxSize = { 300, 100 };
    SetConsoleScreenBufferSize(hConsole, maxSize);
    system("mode con cols=180 lines=55");
}

class MyGame : public Engine {
private:
    Camera camera;
    Raycaster raycaster;

    bool mouseControlEnabled = true;
    float mouseSensitivity = 0.003f;
    bool flyMode = true;

public:
    MyGame() : Engine(180, 55) {
        camera.position = { 5, 0.5f, 5 };
        camera.rotation = { 0, 0, 0 };
        camera.fov = 60.0f;
        camera.nearPlane = 0.1f;

        raycaster.SetFlyMode(flyMode);
        raycaster.SetColors(0x0009, 0x0002, 0x000E, 0x0006);
        raycaster.SetWallChar(L'#');
        raycaster.SetFOV(0.66f);

        SetDebugCamera(&camera);
    }

    void OnStart() override {
        Engine::OnStart();

        std::cout << "\n========================================\n";
        std::cout << "  3D CONSOLE ENGINE - RAYCASTER       \n";
        std::cout << "========================================\n";
        std::cout << "  Controls:                           \n";
        std::cout << "    WASD    - Move                    \n";
        std::cout << "    Mouse   - Look around (FULL 360°) \n";
        std::cout << "    Q/E     - Fly up/down (FLY ON)    \n";
        std::cout << "    F       - Toggle FLY mode         \n";
        std::cout << "    M       - Toggle Mouse capture    \n";
        std::cout << "    ESC     - Exit                    \n";
        std::cout << "========================================\n";

        Input* input = GetInput();
        if (input) {
            input->SetMouseCapture(true);
            std::cout << "[Mouse] Captured!\n";
        }

        std::cout << "[FLY] Mode: " << (flyMode ? "ON" : "OFF") << "\n";
    }

    void OnUpdate(float deltaTime) override {
        Engine::OnUpdate(deltaTime);

        Input* input = GetInput();
        if (!input) return;

        float moveSpeed = 3.0f * deltaTime;

        if (mouseControlEnabled && input->IsMouseCaptured()) {
            camera.rotation.y -= input->GetMouseDeltaX() * mouseSensitivity;
            camera.rotation.x += input->GetMouseDeltaY() * mouseSensitivity;
        }

        Vec3 forward = camera.GetForward();
        Vec3 right = camera.GetRight();

        Vec3 moveDelta = { 0, 0, 0 };

        if (input->IsKeyDown(KeyCode::W)) moveDelta += forward * moveSpeed;
        if (input->IsKeyDown(KeyCode::S)) moveDelta -= forward * moveSpeed;
        if (input->IsKeyDown(KeyCode::A)) moveDelta -= right * moveSpeed;
        if (input->IsKeyDown(KeyCode::D)) moveDelta += right * moveSpeed;

        if (flyMode) {
            if (input->IsKeyDown(KeyCode::Q)) moveDelta.y += moveSpeed;
            if (input->IsKeyDown(KeyCode::E)) moveDelta.y -= moveSpeed;
        }

        raycaster.MoveCamera(camera, moveDelta);

        if (input->IsKeyPressed(KeyCode::F)) {
            flyMode = !flyMode;
            raycaster.SetFlyMode(flyMode);
            std::cout << "[FLY] Mode: " << (flyMode ? "ON" : "OFF") << "\n";
            if (!flyMode) camera.position.y = 0.5f;
        }

        if (input->IsKeyPressed(KeyCode::M)) {
            mouseControlEnabled = !mouseControlEnabled;
            input->SetMouseCapture(mouseControlEnabled);
            std::cout << "[Mouse] Capture: " << (mouseControlEnabled ? "ON" : "OFF") << "\n";
        }
    }

    void OnRender(float deltaTime) override {
        if (!GetBuffer()) return;

        GetBuffer()->Clear(L' ', 0x0000);
        raycaster.Render(*GetBuffer(), camera, deltaTime);
        GetBuffer()->Render();
    }

    void OnDestroy() override {
        Engine::OnDestroy();

        Input* input = GetInput();
        if (input) {
            input->SetMouseCapture(false);
        }
        std::cout << "[Mouse] Released!\n";
    }
};

int main() {
    SetFullscreen();
    system("title 3D Console Engine - Raycaster");

    MyGame game;
    game.Run();

    return 0;
}