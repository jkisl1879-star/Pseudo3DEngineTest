#pragma once
#include "Scene/GameObject.h"
#include <memory>
#include <vector>

namespace Engine {
    class Scene {
    private:
        std::vector<std::unique_ptr<GameObject>> objects;

    public:
        void AddObject(std::unique_ptr<GameObject> obj) {
            obj->Start();
            objects.push_back(std::move(obj));
        }

        void Update(float deltaTime) {
            for (auto& obj : objects) {
                if (obj->isActive) {
                    obj->Update(deltaTime);
                }
            }
        }

        void Render(ConsoleBuffer& buffer) {
            for (auto& obj : objects) {
                if (obj->isActive) {
                    obj->Render(buffer);
                }
            }
        }

        GameObject* FindObjectByName(const std::string& name) {
            for (auto& obj : objects) {
                if (obj->name == name) {
                    return obj.get();
                }
            }
            return nullptr;
        }

        void Clear() {
            objects.clear();
        }
    };
}