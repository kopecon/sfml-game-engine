//
// Created by Andrew on 24/01/2026.
//

#include "../../../../Includes/Game/Engines/SceneGraph/RectangleShape.hpp"


RectangleShape::RectangleShape() :
    rectangleShape_(std::make_unique<sf::RectangleShape>())
    {}

RectangleShape::RectangleShape(const sf::Vector2f &size) :
    rectangleShape_(std::make_unique<sf::RectangleShape>(size))
    {}

Colorable * RectangleShape::asColorable() {
    return this;
}

void RectangleShape::applyColor(const sf::Color color) {
    rectangleShape_->setFillColor(color);
}

sf::RectangleShape & RectangleShape::getShape() {
    return *rectangleShape_;
}

const sf::RectangleShape & RectangleShape::getShape() const {
    return *rectangleShape_;
}

inline void RectangleShape::drawSelf(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(*rectangleShape_, states);
}

std::optional<sf::FloatRect> RectangleShape::getSelfGlobalBounds() const {
    return rectangleShape_->getLocalBounds();
}