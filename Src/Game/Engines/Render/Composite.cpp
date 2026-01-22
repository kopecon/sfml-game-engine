//
// Created by Andrew on 05/01/2026.
//

#include "../../../../Utils/utils.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "../../../../Includes/Game/Engines/Render/Composite.hpp"

#include <iostream>

#include "../../../../Includes/Game/Engines/AnimationEngine/Animatable.hpp"


#pragma region constructors
Composite::Composite() = default;

Composite::Composite(std::unique_ptr<sf::Sprite> sprite) :
    sprite_(std::move(sprite))
    {}
#pragma endregion

bool Composite::hasSprite() const {
    if (sprite_) {
        return true;
    }
    return false;
}

void Composite::add(std::unique_ptr<Composite> composite) {
    composite->setOrigin({0.f, 0.f});
    children.push_back(std::move(composite));
}

void Composite::add(std::unique_ptr<sf::Sprite> sprite, std::string name) {
    if (!sprite_) {
        setSprite(std::move(sprite));
    }
    else {
        sprite->setOrigin({0.f, 0.f});
        auto composite = std::make_unique<Composite>();
        composite->rename(name_ + "_" + std::move(name));
        composite->setSprite(std::move(sprite));
        add(std::move(composite));
    }
}

Animatable * Composite::asAnimatable() {
    return nullptr;
}

bool Composite::play(float dt) {
    // Own animation
    if (const auto animated = asAnimatable()) {
        animated->animate(dt);
        return true;
    }
    // Children animation
    for (const auto &pChild : children) {
        pChild->play(dt);
    }
    return false;
}

void Composite::rename(std::string name) {
    name_ = std::move(name);
}

void Composite::setSprite(std::unique_ptr<sf::Sprite> sprite) {
    sprite_ = std::move(sprite);
}

void Composite::setColor(const sf::Color &color) const {
    for (const auto &pSprite : getAllSprites()) {
        pSprite->setColor(color);
    }
}

void Composite::showOutline(const sf::Color color) {
    auto bounds = getLocalBounds();
    auto boundary = std::make_unique<sf::RectangleShape>(bounds.size);
    boundary->setPosition(bounds.position);
    boundary->setFillColor(sf::Color::Transparent);
    boundary->setOutlineColor(color);
    boundary->setOutlineThickness(5.f);
    outline_ = std::move(boundary);
}

sf::FloatRect Composite::getLocalBounds() const {
    //CHATGPT SOLUTION
    bool initialized = false;

    sf::Vector2f minPos;
    sf::Vector2f maxPos;

    auto absorb = [&](const sf::FloatRect& r) {
        sf::Vector2f rMin = r.position;
        sf::Vector2f rMax = r.position + r.size;

        if (!initialized) {
            minPos = rMin;
            maxPos = rMax;
            initialized = true;
        } else {
            minPos.x = std::min(minPos.x, rMin.x);
            minPos.y = std::min(minPos.y, rMin.y);
            maxPos.x = std::max(maxPos.x, rMax.x);
            maxPos.y = std::max(maxPos.y, rMax.y);
        }
    };

    if (sprite_) {
        absorb(sprite_->getGlobalBounds());
    }

    for (const auto& child : children) {
        absorb(child->getGlobalBounds());
    }

    if (!initialized)
        return {};

    return { minPos, maxPos - minPos };
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

sf::Sprite& Composite::getSprite() const {
    assert(sprite_);
    return *sprite_;
}

std::string_view Composite::getName() const {
    return name_;
}

std::vector<sf::Sprite*> Composite::getAllSprites() const {
    std::vector<sf::Sprite*> sprites{};
    if (sprite_) {
        sprites.push_back(sprite_.get());
    }
    for (const auto &pComposite : children) {
        std::vector<sf::Sprite*> subSprites = pComposite->getAllSprites();
        sprites.insert(sprites.begin(), subSprites.begin(), subSprites.end());
    }
    return sprites;
}

void Composite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // DRAW MAIN SPRITE
    if (sprite_) {
        // apply the texture
        states.texture = &sprite_->getTexture();
        target.draw(*sprite_, states);
    }
    // DRAW OTHER COMPOSITES
    for (const auto &child : children) {
        target.draw(*child, states);
    }
    // DRAW BOUNDARY
    if (outline_) {
        target.draw(*outline_, states);
    }
}
