#include <utility>
#include "Game/World/World.hpp"
#include "Game/Game.hpp"
#include "Utils/utils.hpp"


#pragma region constructors
World::World(Game &game, std::string name)
    : game(game),
      name_(text::up(std::move(name))) {
}
#pragma endregion


std::string World::getName() const {
    return name_;
}

void World::update() {
    for (const auto &entity: entities_ | std::views::values) {
        entity->update();
        // Remove flagged entities
        if (entity->removalFlag) {
            remove(*entity);
        }
    }
}
