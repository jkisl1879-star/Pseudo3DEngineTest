#pragma once
#include "Core/GameLoop.h"
#include "Graphics/ConsoleBuffer.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include <memory>

namespace Engine {
    class Camera;
}

namespace Engine {
    class Engine : public GameLoop {
    private:
        std::unique_ptr<ConsoleBuffer> buffer;
        std::unique_ptr<Input> input;
        std::unique_ptr<Scene> currentScene;

        int screenWidth = 180;
        int screenHeight = 55;

    public:
        Engine(int width = 180, int height = 55);
        ~Engine() = default;

        void OnStart() override;
        void OnUpdate(float deltaTime) override;
        void OnRender(float deltaTime) override;
        void OnDestroy() override;

        Scene* GetScene();
        Input* GetInput();
        ConsoleBuffer* GetBuffer();
        void SetScreenSize(int width, int height);
        void SetDebugCamera(const Camera* cam);

    private:
        void DrawDebugInfo();
        void DrawSky();
    };
}