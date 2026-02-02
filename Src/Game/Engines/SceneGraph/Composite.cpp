//
// Created by Andrew on 05/01/2026.
//

#include "Game/Engines/SceneGraph/Composite.hpp"
#include "Game/Engines/SceneGraph/Colorable.hpp"
#include "Game/Engines/AnimationEngine/Animatable.hpp"
#include <iostream>


#pragma region constructors
Composite::Composite() = default;
#pragma endregion

void Composite::play(const float dt) {
    // Own animation
    if (const auto animated = asAnimatable()) {
        animated->animate(dt);
    }
    // Children animation
    for (const auto &pChild : children_) {
        pChild->play(dt);
    }
}

void Composite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform(); // PROPAGATE TRANSFORM
    drawSelf(target, states);
    drawChildren(target, states);
    drawOutline(target, states);
}

void Composite::rename(std::string name) {
    name_ = std::move(name);
}

void Composite::setColor(const sf::Color &color) {
    // Color self
    if (const auto colorable = asColorable()) {
        colorable->applyColor(color);
    }
    // Color children
    for (const auto &child : getChildren()) {
        if (const auto colorable = child->asColorable()) {
            colorable->applyColor(color);
        }
    }
}

void Composite::showOutline(const sf::Color color) {
    const auto bounds = getLocalBounds();
    auto boundary = std::make_unique<sf::RectangleShape>();
    boundary->setSize(bounds.size);
    boundary->setPosition(bounds.position);
    boundary->setFillColor(sf::Color::Transparent);
    boundary->setOutlineColor(color);
    boundary->setOutlineThickness(5.f);
    outline_ = std::move(boundary);
}

Animatable * Composite::asAnimatable() {
    return nullptr;
}

Colorable * Composite::asColorable() {
    return nullptr;
}

sf::FloatRect Composite::getLocalBounds() const {
    bool initialized = false;

    sf::Vector2f minPos;
    sf::Vector2f maxSize;

    auto absorb = [&](const sf::FloatRect& bounds) {
        const sf::Vector2f childMinPos = bounds.position;
        const sf::Vector2f childMaxSize = bounds.position + bounds.size;

        if (!initialized) {
            minPos = childMinPos;
            maxSize = childMaxSize;
            initialized = true;
        } else {
            minPos.x = std::min(minPos.x, childMinPos.x);
            minPos.y = std::min(minPos.y, childMinPos.y);
            maxSize.x = std::max(maxSize.x, childMaxSize.x);
            maxSize.y = std::max(maxSize.y, childMaxSize.y);
        }
    };

    if (const auto selfBounds = getSelfGlobalBounds()) {
        absorb(*selfBounds);
    }

    for (const auto& child : children_) {
        absorb(child->getGlobalBounds());
    }

    if (!initialized)
        return {};

    return {minPos, maxSize - minPos};
}

sf::FloatRect Composite::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}

sf::Vector2f Composite::getCenter() const {
    const auto localBounds = getLocalBounds();
    const auto x = localBounds.position.x + localBounds.size.x / 2.f;
    const auto y = localBounds.position.y + localBounds.size.y / 2.f;
    return {x, y};
}

std::string_view Composite::getName() const {
    return name_;
}

std::vector<std::unique_ptr<Composite>>& Composite::getChildren() {
    return children_;
}

std::optional<sf::FloatRect> Composite::getSelfGlobalBounds() const {
    return std::nullopt;
}

void Composite::drawChildren(sf::RenderTarget &target, const sf::RenderStates states) const {
    for (const auto &child : children_) {
        target.draw(*child, states);
    }
}

void Composite::drawOutline(sf::RenderTarget &target, const sf::RenderStates states) const {
    if (outline_) {
        const sf::FloatRect newBounds = states.transform.transformRect(getLocalBounds());
        outline_->setSize(newBounds.size);
        outline_->setPosition(newBounds.position);
        target.draw(*outline_);
    }
}
