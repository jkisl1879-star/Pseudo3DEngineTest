#include "Core/Engine.h"
#include "Core/Camera.h"
#include <string>
#include <iostream>
#include <windows.h>

namespace Engine {
    Engine::Engine(int width, int height) : screenWidth(width), screenHeight(height) {}

    void Engine::OnStart() {
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_MAXIMIZE);

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD maxSize = { 300, 100 };
        SetConsoleScreenBufferSize(hConsole, maxSize);

        SetWindowLong(hwnd, GWL_STYLE,
            GetWindowLong(hwnd, GWL_STYLE) & ~WS_VSCROLL & ~WS_HSCROLL);

        buffer = std::make_unique<ConsoleBuffer>(screenWidth, screenHeight);
        input = std::make_unique<Input>();
        currentScene = std::make_unique<Scene>();

        system("mode con cols=180 lines=55");
    }

    void Engine::OnUpdate(float deltaTime) {
        if (input) {
            input->Update();
        }

        if (input && input->IsKeyPressed(KeyCode::Escape)) {
            Stop();
        }

        if (currentScene) {
            currentScene->Update(deltaTime);
        }
    }

    void Engine::OnRender(float deltaTime) {
        if (!buffer) return;

        DrawSky();
        DrawDebugInfo();
        buffer->Render();
    }

    void Engine::OnDestroy() {}

    void Engine::DrawSky() {
        if (!buffer) return;

        int width = buffer->GetWidth();
        int height = buffer->GetHeight();

        WORD bgColor = 0x000B;
        WORD color = (0x000F) | (bgColor << 4);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                buffer->SetPixel(x, y, L' ', color);
            }
        }
    }

    void Engine::DrawDebugInfo() {
        if (!buffer) return;

        std::wstring fps = L"FPS: " + std::to_wstring(static_cast<int>(1.0f / GetDeltaTime()));
        int len = static_cast<int>(fps.size());
        for (int i = 0; i < len && i < buffer->GetWidth(); ++i) {
            buffer->SetPixel(buffer->GetWidth() - len + i, 0, fps[i], 0x000A | (0x0000 << 4));
        }
    }

    Scene* Engine::GetScene() { return currentScene.get(); }
    Input* Engine::GetInput() { return input.get(); }
    ConsoleBuffer* Engine::GetBuffer() { return buffer.get(); }
    void Engine::SetScreenSize(int width, int height) {
        screenWidth = width;
        screenHeight = height;
    }

    void Engine::SetDebugCamera(const Camera* cam) {
        // Для отладки
    }
}