//
// Created by Andrew on 27/11/2025.
//

#include "../Includes/World.hpp"

World::World() = default;

World::World(const char *name): name(name) {}

void World::draw() const {
    for (auto &entity: entities | std::views::values) {
        if (!entity->pShapes.empty()) {
            for (const auto *shape : entity->pShapes) {
                pGame->video.window.draw(*shape);
            }
        }
        else pGame->video.window.draw(*entity->pShape);
    }
}

void World::update() {
    for (auto &entity : entities | std::views::values) {
        entity->update();
        // Clear removed entities
        if (entity->markedForRemoval) {
            // remove(entity);
        }
    }
}
