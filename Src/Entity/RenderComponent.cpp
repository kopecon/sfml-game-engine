//
// Created by Andrew on 30/12/2025.
//

#include "../../Includes/Entity/RenderComponent.hpp"

#include <iostream>

#include "../../Includes/Entity/Entity.hpp"

namespace entity {
    RenderComponent::RenderComponent(Entity &entity):entity(entity) {}

    void RenderComponent::addShape(std::unique_ptr<sf::Shape> shape) {
        shapes.push_back(std::move(shape));
    }

    sf::Shape & RenderComponent::getShape(const sf::Shape &shape) {
        const auto it = std::ranges::find_if(
            shapes,
            [&shape](const std::unique_ptr<sf::Shape>& obj) {
                return obj.get() == &shape;
            });
        if (it == shapes.end()) std::cout << "Shape not found.\n";
        return *it->get();
    }

    const std::vector<std::unique_ptr<sf::Shape>> & RenderComponent::getShapes() const {
        return shapes;
    }

    void RenderComponent::stretchToWidth(sf::RectangleShape *pShape) const {
        pShape->setSize({
            static_cast<float>(entity.game.video.window.getSize().x),
            pShape->getSize().y
            }
        );
    }

    void RenderComponent::repeatToWidth(sf::RectangleShape *pShape) const {
        stretchToWidth(pShape);
        pShape->setTextureRect(
        sf::IntRect({0, 0}, static_cast<sf::Vector2i>(pShape->getGlobalBounds().size))
        );
    }

    void RenderComponent::move(const sf::Vector2f &offset) const {
        for (const auto &pShape : shapes) {
            pShape->move(offset);
        }
    }

    void RenderComponent::setFillColor(const sf::Color &color) const {
        for (const auto &pShape : shapes) {
            pShape->setFillColor(color);
        }
    }

    void RenderComponent::setPosition(const sf::Vector2f &position) const {
        /* Sets position to every shape, but keeps the relative position
             * to the first shape for each other shape.
             */
        if (shapes.empty()) return;
        auto &root = *shapes.begin()->get();
        for (int i=1; i<shapes.size(); ++i) {
            const auto posDif = root.getPosition() - shapes[i]->getPosition();
            const auto newPos = position - posDif;
            shapes[i]->setPosition(newPos);
        }
        root.setPosition(position);
    }


    void RenderComponent::update() const {
        setPosition(entity.position);
    }
} // entity