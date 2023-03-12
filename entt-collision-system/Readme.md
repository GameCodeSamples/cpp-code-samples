The CollisionSystem class is responsible for checking collisions and triggering events when a collision occurs. It does this by iterating over all entities in the registry that have a Position component and either a Size or Circle component, and checking if they intersect with any other entities.

To check for collisions between entities, the CollisionSystem class uses a combination of AABB (Axis-Aligned Bounding Box) and circle-circle collision detection algorithms. It first checks if the bounding boxes of two entities overlap, and if they do, it checks if the circles (if any) of the two entities intersect.

When a collision is detected, the CollisionSystem class triggers the onCollision event and passes the entities involved in the collision as arguments.
