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


namespace entity {
    class Entity;

    class ShapeComposite final : public sf::Drawable, public sf::Transformable {
    protected:
        std::vector<std::unique_ptr<sf::Shape>> shapes{};
    public:
        ShapeComposite() = default;

        void addShape(std::unique_ptr<sf::Shape> shape);

        void setFillColor(const sf::Color &color) const;

        sf::Shape& getShape(const sf::Shape &shape);

        [[nodiscard]] const std::vector<std::unique_ptr<sf::Shape>>& getShapes() const;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

            for (const auto &pShape : shapes) {
                // apply the entity's transform -- combine it with the one that was passed by the caller

                // apply the texture
                states.texture = pShape->getTexture();

                // you may also override states.shader or states.blendMode if you want

                // draw the vertex array
                target.draw(*pShape, states);
            }
        }
    };

    class RenderComponent final: public sf::Drawable {
    protected:
        std::vector<std::unique_ptr<ShapeComposite>> composites{};
        Entity &entity;
    public:
        explicit RenderComponent(Entity &entity);

        [[nodiscard]] const std::vector<std::unique_ptr<ShapeComposite>>& getShapeComposites() const;

        void stretchToWidth(sf::RectangleShape *pShape) const;

        void repeatToWidth(sf::RectangleShape *pShape) const;

        void addComposite(std::unique_ptr<ShapeComposite> composite);

        void setFillColor(const sf::Color &color) const;

        [[nodiscard]] sf::Shape& getShape() const;

        ShapeComposite& getShapeComposite(const ShapeComposite &composite);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            for (const auto &pComposite : composites) {
                target.draw(*pComposite);
            }
        }

        void update() const;
    };
} // entity

#endif //BONK_GAME_RENDER_COMPONENT_HPP