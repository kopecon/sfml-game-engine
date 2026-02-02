//
// Created by Andrew on 27/11/2025.
//

#include <utility>
#include <iostream>
#include "Game/World/Entity/Entity.hpp"
#include "Game/World/World.hpp"


namespace entity {

#pragma region constructors
    Entity::~Entity() {
        std::cout << "Entity: " << name_ << " removed.\n";
    }

    Entity::Entity(World &world, const entityID ID, std::string name):
        id_(ID),
        name_(std::move(name)),
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

    void Entity::rename(std::string entityName) {
        //TODO: check nonexistence before renaming
        name_ = std::move(entityName);
    }

    std::string_view Entity::getName() {
        return name_;
    }

    std::string Entity::getClassName() {
        return "Entity";
    }

    entityID Entity::getID() const {return id_;}
}

