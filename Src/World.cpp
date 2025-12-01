//
// Created by Andrew on 27/11/2025.
//

#include "../Includes/World.hpp"

void World::add(Entity &entity) {
    entities.emplace(entities.end(), &entity);
    entity.pWorld = this;
}

void World::remove(const Entity *entity) {
    // If the element is found, erase it
    // Removes all occurrences
    std::erase(entities, entity);
}

void World::draw() const {
    for (const auto *entity : entities) {
        if (!entity->pShapes.empty()) {
            for (const auto *shape : entity->pShapes) {
                pGame->video.window.draw(*shape);
            }
        }
        else pGame->video.window.draw(*entity->pShape);
    }
}

void World::update() {
    for (auto *entity : entities) {
        entity->update();
        // Clear removed entities
        if (entity->markedForRemoval) {
            remove(entity);
        }
    }
}
