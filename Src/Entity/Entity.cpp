//
// Created by Andrew on 27/11/2025.
//

#include <utility>
#include "../../Includes/Entity/Entity.hpp"

#include <iostream>

#include "../../Utils/utils.hpp"
#include "../../Includes/World/World.hpp"
#include "SFML/Graphics/Texture.hpp"


Entity::~Entity() = default;

Entity::Entity(std::string name) {
    text::up(name);
    this->name = std::move(name);
}

void Entity::init() {
    std::cout << "Base Init: " << this->name << " ...Start" << "\n";
    this->pShape->setOrigin(pShape->getGeometricCenter());
    std::cout << "Base Init: " << this->name << " ...Finish" << "\n";
}

void Entity::update() {}

bool Entity::operator==(const Entity &other) const {
    return this == &other;
}

bool Entity::operator!=(const Entity &other) const {
    return this != &other;
}
