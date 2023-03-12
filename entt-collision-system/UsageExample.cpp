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