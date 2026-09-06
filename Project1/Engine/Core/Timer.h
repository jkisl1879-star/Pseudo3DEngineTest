//Timer.h
#pragma once
#include <chrono>

namespace Engine {
    class Timer {
    private:
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point previousTime;
        float deltaTime = 0.0f;
        float totalTime = 0.0f;

    public:
        Timer() {
            startTime = std::chrono::steady_clock::now();
            previousTime = startTime;
        }

        void Tick() {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> delta = currentTime - previousTime;
            deltaTime = delta.count();
            totalTime += deltaTime;
            previousTime = currentTime;
        }

        float GetDeltaTime() const { return deltaTime; }
        float GetTotalTime() const { return totalTime; }
    };
}