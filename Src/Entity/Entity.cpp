//
// Created by Andrew on 27/11/2025.
//

#include <utility>
#include "../../Includes/Entity/Entity.hpp"

#include <iostream>

#include "../../Utils/utils.hpp"
#include "../../Includes/World/World.hpp"


Entity::~Entity() = default;

Entity::Entity(std::string name) {
    text::up(name);
    this->name = std::move(name);
}

sf::Vector2f Entity::getWindowToShapeSizeRatio() const {
        const sf::Vector2f windowSize = static_cast<sf::Vector2f>(pWorld->pGame->video.windowSize);
        const sf::Vector2f shapeSize = pShape->getGlobalBounds().size;
        const sf::Vector2f sizeRatio = {
            windowSize.x / shapeSize.x,
            windowSize.y / shapeSize.y,
        };
        return sizeRatio;
    }

void Entity::init() {
    std::cout << "Base Init: " << name << " ...Start" << "\n";
    pShape = getShape();
    pTexture = getTexture();
    initShapeSize();
    pShape->setOrigin(pShape->getGeometricCenter());
    pShape->setTexture(pTexture);
    std::cout << "Base Init: " << name << " ...Finish" << "\n\n";
}

void Entity::update() {}

bool Entity::operator==(const Entity &other) const {
    return this == &other;
}

bool Entity::operator!=(const Entity &other) const {
    return this != &other;
}
