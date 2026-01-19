//
// Created by Andrew on 27/11/2025.
//

#include <utility>
#include "../../Includes/Entity/Entity.hpp"

#include <iostream>
#include "../../Includes/World/World.hpp"
#include "../../Includes/Game/Game.hpp"


namespace entity {

#pragma region constructors
    Entity::~Entity() {
        std::cout << "Entity: " << name << " removed.\n";
    }

    Entity::Entity(World &world, const entityID ID, std::string name):
        ID(ID),
        name(std::move(name)),
        world(world),
        game(world.game),
        render(*this)
        {}
#pragma endregion

#pragma region operators
    bool Entity::operator==(const Entity &other) const {
        return this == &other;
    }

    bool Entity::operator!=(const Entity &other) const {
        return this != &other;
    }
#pragma endregion

    void Entity::setName(std::string entityName) {
        name = std::move(entityName);
    }

    std::string_view Entity::getName() {
        return name;
    }

    std::string Entity::getClassName() {
        return "Entity";
    }
}

