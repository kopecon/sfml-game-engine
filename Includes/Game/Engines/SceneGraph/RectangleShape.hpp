//
// Created by Andrew on 24/01/2026.
//

#ifndef BONK_GAME_RECTANGLE_SHAPE_HPP
#define BONK_GAME_RECTANGLE_SHAPE_HPP
#include "Game/Engines/SceneGraph/Composite.hpp"
#include "Game/Engines/SceneGraph/Colorable.hpp"


class RectangleShape final : public Composite, public Colorable {
protected:
    std::unique_ptr<sf::RectangleShape> rectangleShape_{nullptr};

public:

    explicit RectangleShape();

    explicit RectangleShape(const sf::Vector2f &size);

    Colorable *asColorable() override ;

    void applyColor(sf::Color color) override;

    [[nodiscard]] sf::RectangleShape& getShape();

    [[nodiscard]] const sf::RectangleShape& getShape() const;

private:
    void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::optional<sf::FloatRect> getSelfGlobalBounds() const override;

};


#endif //BONK_GAME_RECTANGLE_SHAPE_HPP