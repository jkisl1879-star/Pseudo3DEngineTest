#pragma once
#include "Math/Transform.h"
#include "Graphics/Sprite.h"
#include "Graphics/ConsoleBuffer.h"
#include <string>

namespace Engine {
    class GameObject {
    public:
        std::string name;
        Transform transform;
        Sprite sprite;
        bool isActive = true;

        GameObject(const std::string& name = "GameObject") : name(name) {}

        virtual ~GameObject() = default;

        virtual void Start() {}
        virtual void Update(float deltaTime) {}
        virtual void Render(ConsoleBuffer& buffer) {
            if (isActive && sprite.width > 0 && sprite.height > 0) {
                buffer.DrawSprite(static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    sprite);
            }
        }
    };
}