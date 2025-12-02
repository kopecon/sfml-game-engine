//
// Created by Andrew on 27/11/2025.
//

#include "../Includes/Entity.hpp"

#include "SFML/Graphics/Texture.hpp"

Entity::~Entity() = default;

Entity::Entity(const char *name): name(name) {}


void Entity::init(sf::Shape &shape, sf::Texture &texture) {
    pShape = &shape;
    pTexture = &texture;
    shape.setOrigin(shape.getGeometricCenter());
    shape.setTexture(&texture);
}

void Entity::update() {
}

bool Entity::operator==(const Entity &other) const {
    return this == &other;
}

bool Entity::operator!=(const Entity &other) const {
    return this != &other;
}
