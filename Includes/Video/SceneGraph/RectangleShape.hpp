#pragma once

#include "Video/SceneGraph/Colorable.hpp"
#include "Video/SceneGraph/Composite.hpp"


namespace render {
    class RectangleShape : public Composite, public Colorable {
    protected:
        std::unique_ptr<sf::RectangleShape> rectangleShape_{nullptr};

    public:
        explicit RectangleShape();

        explicit RectangleShape(const sf::Vector2f &size);

        Colorable *asColorable() noexcept override;

        void applyColor(sf::Color color) noexcept override;

        void setSize(const sf::Vector2f size) const noexcept;

        [[nodiscard]] Transformable &kernel() noexcept override;

        [[nodiscard]] const Transformable &kernel() const noexcept override;

    private:
        void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const noexcept override;

        std::optional<sf::FloatRect> getSelfGlobalBounds() const noexcept override;

        void updateNormals() noexcept override;
    };
} // render
