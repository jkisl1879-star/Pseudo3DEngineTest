#pragma once
#include "Core/Timer.h"

namespace Engine {
    class GameLoop {
    private:
        Timer timer;
        bool isRunning = false;
        float fixedTimeStep = 1.0f / 60.0f;
        float accumulator = 0.0f;

    public:
        virtual ~GameLoop() = default;

        void Run() {
            isRunning = true;
            OnStart();

            while (isRunning) {
                timer.Tick();
                accumulator += timer.GetDeltaTime();

                while (accumulator >= fixedTimeStep) {
                    OnUpdate(fixedTimeStep);
                    accumulator -= fixedTimeStep;
                }

                OnRender(timer.GetDeltaTime());
            }

            OnDestroy();
        }

        void Stop() { isRunning = false; }

        virtual void OnStart() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender(float deltaTime) {}
        virtual void OnDestroy() {}

        float GetDeltaTime() const { return timer.GetDeltaTime(); }
        float GetTotalTime() const { return timer.GetTotalTime(); }
    };
}