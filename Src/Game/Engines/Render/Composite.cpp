//
// Created by Andrew on 05/01/2026.
//

#include "../../../../Includes/Game/Engines/Render/Composite.hpp"
#include "../../../../Utils/utils.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>

#include "SFML/Graphics/RectangleShape.hpp"


void Composite::addShape(std::unique_ptr<sf::Shape> shape) {
    shape->setOrigin({0.f, 0.f});
    shapes.push_back(std::move(shape));
}

void Composite::setFillColor(const sf::Color &color) const {
    for (const auto &pShape : shapes) {
        pShape->setFillColor(color);
    }
}

void Composite::showBoundary(const sf::Color color) {
    auto bounds = getGlobalBounds();
    auto outline = std::make_unique<sf::RectangleShape>(bounds.size);
    outline->setPosition(bounds.position);
    outline->setFillColor(sf::Color::Transparent);
    outline->setOutlineColor(color);
    outline->setOutlineThickness(5.f);
    boundary = std::move(outline);
}

sf::FloatRect Composite::getLocalBounds() const {
    sf::Vector2f minPosition{};
    sf::Vector2f maxSize{};
    for (const auto &pShape : shapes) {
        sf::FloatRect bounds = pShape->getGlobalBounds();
        minPosition.x = std::min(minPosition.x, bounds.position.x);
        minPosition.y = std::min(minPosition.y, bounds.position.y);
        maxSize.x = std::max(maxSize.x, bounds.position.x + bounds.size.x);
        maxSize.y = std::max(maxSize.y, bounds.position.y + bounds.size.y);
    }
    return {minPosition, -minPosition + maxSize};
}

sf::FloatRect Composite::getGlobalBounds() const {
    const auto localBounds = getLocalBounds();
    const auto position = hd::multiply(localBounds.position, getScale());
    const auto size = hd::multiply(localBounds.size, hd::abs(getScale()));
    return {position, size};
}

sf::Vector2f Composite::getCenter() const {
    const auto localBounds = getLocalBounds();
    const auto x = localBounds.position.x + localBounds.size.x / 2.f;
    const auto y = localBounds.position.y + localBounds.size.y / 2.f;
    return {x, y};
}

sf::Shape& Composite::getShape(const sf::Shape &shape) {
    const auto it = std::ranges::find_if(
        shapes,
        [&shape](const std::unique_ptr<sf::Shape>& obj) {
            return obj.get() == &shape;
        });
    if (it == shapes.end()) std::cout << "Shape not found.\n";
    return *it->get();
}

void Composite::enlarge(const float &factor) const {
    for (const auto &pShape : shapes) {
        pShape->setScale(scalar::multiply(pShape->getScale(), factor));
    }
}

void Composite::enlarge(const sf::Vector2f &factor) {
    setScale(hd::multiply(this->getScale(), factor));
}

void Composite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
    if (boundary) target.draw(*boundary, states);
    for (const auto &pShape : shapes) {
        // apply the entity's transform -- combine it with the one that was passed by the caller

        // apply the texture
        states.texture = pShape->getTexture();

        // you may also override states.shader or states.blendMode if you want

        // draw the vertex array
        target.draw(*pShape, states);
    }
}
