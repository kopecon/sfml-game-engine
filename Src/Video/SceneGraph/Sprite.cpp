#include "Video/SceneGraph/Sprite.hpp"

#include "Video/Camera.hpp"
#include "Video/VideoComponent.hpp"


namespace render {
    Sprite::Sprite(const sf::Texture &texture)
        : sprite_(std::make_unique<sf::Sprite>(texture)) {
    }

    Colorable *Sprite::asColorable() noexcept {
        return this;
    }

    void Sprite::applyColor(const sf::Color color) noexcept {
        sprite_->setColor(color);
    }

    void Sprite::repeat(const sf::Vector2u repeats) noexcept {
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

    sf::Sprite &Sprite::getSprite() noexcept {
        assert(sprite_);
        return *sprite_;
    }

    const sf::Sprite &Sprite::getSprite() const noexcept {
        // Read only return
        return *sprite_;
    }

    sf::Transformable & Sprite::kernel() noexcept {
        return *sprite_;
    }

    const sf::Transformable & Sprite::kernel() const noexcept {
        return *sprite_;
    }

    std::optional<sf::FloatRect> Sprite::getSelfGlobalBounds() const noexcept {
        return sprite_->getGlobalBounds();
    }

    void Sprite::drawSelf(sf::RenderTarget &target, const sf::RenderStates states) const noexcept {
        target.draw(*sprite_, states);
    }
} // render
