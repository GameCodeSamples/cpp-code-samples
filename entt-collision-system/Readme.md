The CollisionSystem class is responsible for checking collisions and triggering events when a collision occurs. It does this by iterating over all entities in the registry that have a Position component and either a Size or Circle component, and checking if they intersect with any other entities.

Note that for this porject i also used [Entt](https://github.com/skypjack/entt) as the ECS. 

To check for collisions between entities, the CollisionSystem class uses a combination of AABB (Axis-Aligned Bounding Box) and circle-circle collision detection algorithms. It first checks if the bounding boxes of two entities overlap, and if they do, it checks if the circles (if any) of the two entities intersect.

When a collision is detected, the CollisionSystem class triggers the onCollision event and passes the entities involved in the collision as arguments.

In the following code block you can get some context of how it is used:
```cs

// Initialize the registry and create some entities with Position, Size, and Circle components
entt::registry registry;
auto entity1 = registry.create();
registry.emplace<Position>(entity1, Position{0.0f, 0.0f});
registry.emplace<Size>(entity1, Size{1.0f, 1.0f});
auto entity2 = registry.create();
registry.emplace<Position>(entity2, Position{2.0f, 2.0f});
registry.emplace<Size>(entity2, Size{1.0f, 1.0f});
registry.emplace<Circle>(entity2, Circle{0.5f});

// Create a CollisionSystem and subscribe to the onCollision event
CollisionSystem collisionSystem(registry);
collisionSystem.onCollision.connect([&](auto entity1, auto entity2) {
    std::cout << "Collision detected between entities " << entity1 << " and " << entity2 << std::endl;
});

// Game loop
while (true) {
    // Update the CollisionSystem each frame
    collisionSystem.update();

    // Update game logic and render the scene
    // ...
}

```
