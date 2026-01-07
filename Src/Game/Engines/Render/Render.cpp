#include "../../../../Includes/Game/Engines/Render/Render.hpp"
#include "../../../../Includes/Game/Game.hpp"
#include "../../../../Includes/Entity/Entity.hpp"
#include <iostream>


Render::Render(entity::Entity &entity):entity(entity) {}


void Render::addComposite(std::unique_ptr<Composite> composite) {
    composite->setOrigin({0.f, 0.f});
    composites.push_back(std::move(composite));
}

void Render::addShape(std::unique_ptr<sf::Shape> shape) {
    auto composite = std::make_unique<Composite>();
    composite->addShape(std::move(shape));
    addComposite(std::move(composite));
}

void Render::setFillColor(const sf::Color &color) const {
    for (const auto &pComposite : composites) {
        for (const auto &pShape : pComposite->shapes) {
            pShape->setFillColor(color);
        }
    }
}

void Render::showBoundary(const sf::Color color) {
    auto bounds = getGlobalBounds();
    auto outline = std::make_unique<sf::RectangleShape>(bounds.size);
    outline->setPosition(bounds.position);
    outline->setFillColor(sf::Color::Transparent);
    outline->setOutlineColor(color);
    outline->setOutlineThickness(5.f);
    boundary = std::move(outline);
}

Composite & Render::getComposite(const Composite &composite) {
    const auto it = std::ranges::find_if(
        composites,
        [&composite](const std::unique_ptr<Composite>& obj) {
            return obj.get() == &composite;
        });
    if (it == composites.end()) std::cout << "Composite not found.\n";
    return *it->get();
}

std::vector<std::unique_ptr<Composite>>& Render::getComposites() {
    return composites;
}

sf::FloatRect Render::getLocalBounds() const {
    sf::Vector2f minPosition{};
    sf::Vector2f maxSize{};
    for (const auto &pComposites : composites) {
        sf::FloatRect bounds = pComposites->getGlobalBounds();
        minPosition.x = std::min(minPosition.x, bounds.position.x);
        minPosition.y = std::min(minPosition.y, bounds.position.y);
        maxSize.x = std::max(maxSize.x, bounds.position.x + bounds.size.x);
        maxSize.y = std::max(maxSize.y, bounds.position.y + bounds.size.y);
    }
    return {minPosition, -minPosition + maxSize};
}

sf::FloatRect Render::getGlobalBounds() const {
    const auto localBounds = getLocalBounds();
    const auto position = hd::multiply(localBounds.position, getScale());
    const auto size = hd::multiply(localBounds.size, hd::abs(getScale()));
    return {position, size};
}

sf::Vector2f Render::getCenter() const {
    const auto localBounds = getLocalBounds();
    const auto x = localBounds.position.x + localBounds.size.x / 2.f;
    const auto y = localBounds.position.y + localBounds.size.y / 2.f;
    return {x, y};
}

void Render::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
    if (boundary) target.draw(*boundary, states);
    for (const auto &pComposite : composites) {
        // apply the entity's transform -- combine it with the one that was passed by the caller

        // you may also override states.shader or states.blendMode if you want

        // draw the vertex array
        target.draw(*pComposite, states);
    }
}

void Render::init() {
    setScale(entity.game.video.getWindowToScreenRatio());
}

void Render::update() {
    setPosition(entity.position);
}
