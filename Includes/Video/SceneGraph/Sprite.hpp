#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "Video/SceneGraph/Colorable.hpp"
#include "Video/SceneGraph/Composite.hpp"


class Camera;

namespace render {
    class Sprite : public Composite, public Colorable {
    protected:
        std::unique_ptr<sf::Sprite> sprite_{nullptr};

    public:
        explicit Sprite(const sf::Texture &texture);

        Colorable *asColorable() noexcept override;

        void applyColor(sf::Color color) noexcept override;

        void repeat(sf::Vector2u repeats) noexcept;

        [[nodiscard]] sf::Sprite &getSprite() noexcept;

        [[nodiscard]] const sf::Sprite &getSprite() const noexcept;

        [[nodiscard]] Transformable &kernel() noexcept override;

        [[nodiscard]] const Transformable &kernel() const noexcept override;

    private:
        std::optional<sf::FloatRect> getSelfGlobalBounds() const noexcept override;

        void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const noexcept override;
    };
}
