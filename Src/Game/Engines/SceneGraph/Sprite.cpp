#include "Game/Engines/SceneGraph/Sprite.hpp"
#include "Game/Components/Video/Camera.hpp"
#include "Game/Components/Video/VideoComponent.hpp"


Sprite::Sprite(const sf::Texture &texture)
    : sprite_(std::make_unique<sf::Sprite>(texture)) {
    rename("sprite");
}

Colorable *Sprite::asColorable() {
    return this;
}

void Sprite::applyColor(const sf::Color color) {
    sprite_->setColor(color);
}

void Sprite::repeat(const sf::Vector2u repeats) {
    auto &sprite = getSprite();
    const auto spriteSize = static_cast<sf::Vector2i>(sprite.getGlobalBounds().size);
    sprite.setTextureRect(
        sf::IntRect({0, 0},
                    sf::Vector2i(
                        static_cast<int>(spriteSize.x * repeats.x),
                        static_cast<int>(spriteSize.y * repeats.y)
                    )
        )
    );
}

sf::Sprite &Sprite::getSprite() {
    assert(sprite_);
    return *sprite_;
}

const sf::Sprite &Sprite::getSprite() const {
    // Read only return
    return *sprite_;
}

std::optional<sf::FloatRect> Sprite::getSelfGlobalBounds() const {
    return sprite_->getGlobalBounds();
}

void Sprite::drawSelf(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(*sprite_, states);
}
