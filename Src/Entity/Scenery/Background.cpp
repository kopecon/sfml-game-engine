//
// Created by Andrew on 13/11/2025.
//

#include "../../../Includes/Entity/Scenery/Background.hpp"
#include "../../../Includes/World/World.hpp"

#include <iostream>


Background::Background(std::string name) : Scenery(std::move(name)){}

sf::Texture * Background::getTexture() {
    return &pWorld->pGame->textures.background;
}

void Background::init() {
    Scenery::init();
    shape.setScale({static_cast<float>(stretchFactor), 1});
    shape.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(shape.getGlobalBounds().size)));
    const sf::Vector2f sizeRatio = getWindowToShapeSizeRatio();
    shape.setScale({shape.getScale().x * sizeRatio.x * stretchFactor, shape.getScale().y * sizeRatio.y});
}

