//
// Created by Andrew on 27/11/2025.
//

#include "../Includes/Entity.hpp"

Entity::~Entity() = default;

void Entity::update(const float &dt) {
}

bool Entity::operator==(const Entity &other) const {
    return this == &other;
}

bool Entity::operator!=(const Entity &other) const {
    return this != &other;
}
