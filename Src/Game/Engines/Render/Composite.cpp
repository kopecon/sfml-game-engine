//
// Created by Andrew on 05/01/2026.
//

#include "../../../../Includes/Game/Engines/Render/Composite.hpp"
#include "../../../../Utils/utils.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#pragma region constructors
Composite::Composite() = default;

Composite::Composite(std::string name):
    name(std::move(name))
    {}

Composite::Composite(sf::Texture &texture):
    mainSprite(std::make_unique<sf::Sprite>(texture))
    {}

Composite::Composite(std::unique_ptr<sf::Sprite> sprite):
    mainSprite(std::move(sprite))
    {}

Composite::Composite(std::string name, sf::Texture &texture):
    name(std::move(name)),
    mainSprite(std::make_unique<sf::Sprite>(texture))
    {}

Composite::Composite(std::string name, std::unique_ptr<sf::Sprite> sprite):
    name(std::move(name)),
    mainSprite(std::move(sprite))
    {}
#pragma endregion

void Composite::add(std::unique_ptr<Composite> composite) {
    composite->setOrigin({0.f, 0.f});
    composites.push_back(std::move(composite));
}

void Composite::add(std::unique_ptr<sf::Sprite> newSprite, std::string spriteName) {
    newSprite->setOrigin({0.f, 0.f});
    auto composite = std::make_unique<Composite>(std::move(spriteName), std::move(newSprite));
    add(std::move(composite));
}

void Composite::setSprite(std::unique_ptr<sf::Sprite> newSprite) {
    mainSprite = std::move(newSprite);
}

void Composite::setColor(const sf::Color &color) const {
    for (const auto &pSprite : getAllSprites()) {
        pSprite->setColor(color);
    }
}

void Composite::showBoundary(const sf::Color color) {
    auto bounds = getLocalBounds();
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

    if (mainSprite) {
        const auto mainSpriteBounds = mainSprite->getGlobalBounds();
        minPosition = mainSpriteBounds.position;
        maxSize = mainSpriteBounds.size;
    }
    // SCAN COMPOSITES
    for (const auto &pSprite : getAllSprites()) {
        sf::FloatRect thisSprite = pSprite->getGlobalBounds();
        minPosition.x = std::min(minPosition.x, thisSprite.position.x);
        minPosition.y = std::min(minPosition.y, thisSprite.position.y);
        maxSize.x = std::max(maxSize.x, std::abs(minPosition.x - thisSprite.position.x) + thisSprite.size.x);
        maxSize.y = std::max(maxSize.y, std::abs(minPosition.y - thisSprite.position.y) + thisSprite.size.y);
    }
    const auto result = sf::FloatRect(minPosition, maxSize);
    return result;
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

sf::Sprite* Composite::getSprite() const {
    return mainSprite.get();
}

std::vector<sf::Sprite*> Composite::getAllSprites() const {
    std::vector<sf::Sprite*> sprites{};
    if (mainSprite) {
        sprites.push_back(mainSprite.get());
    }
    for (const auto &pComposite : composites) {
        std::vector<sf::Sprite*> subSprites = pComposite->getAllSprites();
        sprites.insert(sprites.begin(), subSprites.begin(), subSprites.end());
    }
    return sprites;
}

void Composite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // DRAW MAIN SPRITE
    if (mainSprite) {
        // apply the texture
        states.texture = &mainSprite->getTexture();
        target.draw(*mainSprite, states);
    }
    // DRAW OTHER COMPOSITES
    for (const auto &pComposite : composites) {
        pComposite->draw(target, states);
    }

    // DRAW BOUNDARY
    if (boundary) {
        target.draw(*boundary, states);
    }
}
