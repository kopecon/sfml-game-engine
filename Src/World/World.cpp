//
// Created by Andrew on 27/11/2025.
//

#include <utility>
#include "../../Includes/World/World.hpp"
#include "../../Includes/Game/Game.hpp"
#include "../../Utils/utils.hpp"

#pragma region constructors
World::World(Game &game, std::string name):
game(game),
name(text::up(std::move(name))),
groundLevel(static_cast<float>(game.getVideo().getWindowSize().y)*0.7f/2.f)
{}
#pragma endregion


void World::update() {
    for (const auto &entity : entities | std::views::values) {
        entity->update();
        // Remove flagged entities
        if (entity->removalFlag) {
            remove(*entity);
        }
    }
}
