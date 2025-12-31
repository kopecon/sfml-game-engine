//
// Created by Andrew on 30/12/2025.
//

#ifndef BONK_GAME_RENDER_COMPONENT_HPP
#define BONK_GAME_RENDER_COMPONENT_HPP
#include <memory>
#include <vector>

#include "../Game/Game.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/System/Vector2.hpp"


namespace entity {
    class Entity;

    class RenderComponent {
    protected:
        std::vector<std::unique_ptr<sf::Shape>> shapes{};
        Entity &entity;
    public:
        explicit RenderComponent(Entity &entity);;

        void addShape(std::unique_ptr<sf::Shape> shape);

        sf::Shape& getShape(const sf::Shape &shape);

        [[nodiscard]] const std::vector<std::unique_ptr<sf::Shape>>& getShapes() const;

        void stretchToWidth(sf::RectangleShape *pShape) const;

        void repeatToWidth(sf::RectangleShape *pShape) const;

        void move(const sf::Vector2f &offset) const;

        void setFillColor(const sf::Color &color) const;

        void setPosition(const sf::Vector2f &position) const;

        void update() const;
    };
} // entity

#endif //BONK_GAME_RENDER_COMPONENT_HPP