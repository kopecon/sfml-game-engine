//
// Created by Andrew on 27/11/2025.
//

#include <utility>
#include "../../Includes/Entity/Entity.hpp"

#include <iostream>

#include "../../Utils/utils.hpp"
#include "../../Includes/World/World.hpp"
#include "../../Includes/Game/Game.hpp"


namespace entity {

#pragma region constructors
    Entity::~Entity() {
        std::cout << "Entity: " << name << " removed.\n";
    }

    Entity::Entity(World &world, const entityID ID) :
        ID(ID),
        world(world),
        game(world.game),
        render(*this)
        {}

    Entity::Entity(World &world, const entityID ID, std::string name):
        ID(ID),
        name(std::move(name)),
        world(world),
        game(world.game),
        render(*this)
        {}

    std::string Entity::className() const {
        return "Entity";
    }
#pragma endregion

    sf::Vector2f Entity::getWindowToShapeSizeRatio() const {
        const sf::Vector2f windowSize = static_cast<sf::Vector2f>(world.game.video.window.getSize());
        const sf::Vector2f shapeSize = pShape->getGlobalBounds().size;
        const sf::Vector2f sizeRatio = {
            windowSize.x / shapeSize.x,
            windowSize.y / shapeSize.y,
        };
        return sizeRatio;
    }

    void Entity::init() {
        setName(_generateName());
        std::cout << "Base Init: " << name << " Started..." << "\n";
        pShape = getShape();
        pTexture = getTexture();
        initShapeSize();
        pShape->setOrigin(pShape->getGeometricCenter());
        pShape->setTexture(pTexture);
        std::cout << "Base Init: " << name << " Finished." << "\n\n";
    }

    bool Entity::operator==(const Entity &other) const {
        return this == &other;
    }

    bool Entity::operator!=(const Entity &other) const {
        return this != &other;
    }

    std::string Entity::_generateName() const {
        auto result = className() + std::to_string(world.getEntityCount(*this) + 1);
        return result;
    }
}

