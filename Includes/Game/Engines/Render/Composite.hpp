//
// Created by Andrew on 05/01/2026.
//

#ifndef BONK_GAME_COMPOSITE_HPP
#define BONK_GAME_COMPOSITE_HPP
#include <memory>
#include <vector>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Transformable.hpp"


class Composite final : public sf::Drawable, public sf::Transformable {
    std::unique_ptr<sf::RectangleShape> boundary{};
public:
    Composite() = default;

    std::vector<std::unique_ptr<sf::Shape>> shapes{};  // TODO: maybe composites could hold other composites

    void addShape(std::unique_ptr<sf::Shape> shape);

    void setFillColor(const sf::Color &color) const;

    void showBoundary(sf::Color color = sf::Color::Red);

    [[nodiscard]] sf::FloatRect getLocalBounds() const;

    [[nodiscard]] sf::FloatRect getGlobalBounds() const;

    [[nodiscard]] sf::Vector2f getCenter() const;

    [[nodiscard]] sf::Shape& getShape(const sf::Shape &shape);

    void enlarge(const float &factor) const;

    void enlarge(const sf::Vector2f &factor);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //BONK_GAME_COMPOSITE_HPP