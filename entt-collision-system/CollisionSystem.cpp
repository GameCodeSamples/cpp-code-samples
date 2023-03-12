#include <iostream>
#include <entt/entt.hpp>

struct Position {
    float x;
    float y;
};

struct Size {
    float width;
    float height;
};

struct Circle {
    float radius;
};

class CollisionSystem {
public:
    CollisionSystem(entt::registry& registry) : m_registry(registry) {}

    void update() {
        m_registry.view<Position, Size>().each([&](auto entity1, Position& position1, Size& size1) {
            m_registry.view<Position, Size, Circle>().each([&](auto entity2, Position& position2, Size& size2, Circle& circle) {
                if (checkCircleRectangleCollision(position1, size1, position2, size2, circle)) {
                    m_registry.trigger<decltype(onCollision)>(entity1, entity2);
                }
            });

            m_registry.view<Position, Size>().each([&](auto entity2, Position& position2, Size& size2) {
                if (entity1 != entity2 && checkRectangleCollision(position1, size1, position2, size2)) {
                    m_registry.trigger<decltype(onCollision)>(entity1, entity2);
                }
            });
        });
    }

    entt::sink<void(entt::entity, entt::entity)> onCollision = m_registry.sink<void(entt::entity, entt::entity)>();

private:
    bool checkRectangleCollision(Position position1, Size size1, Position position2, Size size2) {
        return position1.x < position2.x + size2.width &&
            position1.x + size1.width > position2.x &&
            position1.y < position2.y + size2.height &&
            position1.y + size1.height > position2.y;
    }

    bool checkCircleRectangleCollision(Position position1, Size size1, Position position2, Size size2, Circle circle) {
        float circleDistanceX = abs(position1.x - position2.x - size2.width / 2.0f);
        float circleDistanceY = abs(position1.y - position2.y - size2.height / 2.0f);

        if (circleDistanceX > (size2.width / 2.0f + circle.radius)) {
            return false;
        }
        if (circleDistanceY > (size2.height / 2.0f + circle.radius)) {
            return false;
        }

        if (circleDistanceX <= (size2.width / 2.0f)) {
            return true;
        }
        if (circleDistanceY <= (size2.height / 2.0f)) {
            return true;
        }

        float cornerDistanceSq = pow(circleDistanceX - size2.width / 2.0f, 2) + pow(circleDistanceY - size2.height / 2.0f, 2);

        return cornerDistanceSq <= pow(circle.radius, 2);
    }

    entt::registry& m_registry;
};