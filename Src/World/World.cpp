//
// Created by Andrew on 27/11/2025.
//

#include <utility>
#include "../../Includes/World/World.hpp"
#include "../../Utils/utils.hpp"


World::World() = default;

World::World(std::string name) {
    text::up(name);
    this->name = std::move(name);
}

void World::draw() const {
    for (auto &entity: entities | std::views::values) {
        pGame->video.window.draw(*entity->pShape);
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
