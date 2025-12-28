//
// Created by Andrew on 27/11/2025.
//

#include "../../../Includes/Entity/Scenery/Ground.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


Ground::Ground(World &world, std::string name) : Scenery(world, std::move(name)) {
    shape.setFillColor(color);
}


const sf::Texture * Ground::getTexture() {
    return &game.textures.topGround;
}

void Ground::init() {
    Scenery::init();
    const sf::Vector2f sizeRatio = getWindowToShapeSizeRatio();
    shape.setScale({sizeRatio.x * stretchFactor, 1});
    shape.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(shape.getGlobalBounds().size)));
    const sf::Vector2f offset = shape.getGeometricCenter() - sf::Vector2f({0.f, shape.getGlobalBounds().size.y/2.f});
    shape.setOrigin(offset);
}
