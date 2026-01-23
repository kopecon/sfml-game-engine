//
// Created by Andrew on 22/01/2026.
//

#include "../../../../Includes/Game/Engines/SceneGraph/Sprite.hpp"

#include <iostream>

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"


Sprite::Sprite(const sf::Texture& texture):
    sprite_(std::make_unique<sf::Sprite>(texture)) {
    rename("sprite");
}

Colorable* Sprite::asColorable() {
    return this;
}

void Sprite::applyColor(const sf::Color color) {
    sprite_->setColor(color);
}

sf::FloatRect Sprite::getLocalBounds() const {
    //TODO: Implement child inclusion
    sf::Vector2f minPos{sprite_->getLocalBounds().position};
    sf::Vector2f maxSize{sprite_->getLocalBounds().size};

    const sf::Vector2f childrenMinPos = getChildrenGlobalBounds().position;
    const sf::Vector2f childrenMaxSize = childrenMinPos + getChildrenGlobalBounds().size;

    minPos.x = std::min(minPos.x, childrenMinPos.x);
    minPos.y = std::min(minPos.y, childrenMinPos.y);
    maxSize.x = std::max(maxSize.x, childrenMaxSize.x);
    maxSize.y = std::max(maxSize.y, childrenMaxSize.y);

    const sf::FloatRect result = {minPos, maxSize};
    return result;
}

sf::Sprite& Sprite::getSprite() const {
    // TODO: possibly bad practice... temporary solution?
    return *sprite_;
}

void Sprite::drawSelf(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(*sprite_, states);
}
