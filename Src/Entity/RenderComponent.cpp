#include "../../Includes/Entity/RenderComponent.hpp"
#include <iostream>
#include "../../Includes/Entity/Entity.hpp"


namespace entity {
    void ShapeComposite::addShape(std::unique_ptr<sf::Shape> shape) {
        shapes.push_back(std::move(shape));
    }

    void ShapeComposite::setFillColor(const sf::Color &color) const {
        for (const auto &pShape : shapes) {
            pShape->setFillColor(color);
        }
    }

    sf::Shape& ShapeComposite::getShape(const sf::Shape &shape) {
        const auto it = std::ranges::find_if(
            shapes,
            [&shape](const std::unique_ptr<sf::Shape>& obj) {
                return obj.get() == &shape;
            });
        if (it == shapes.end()) std::cout << "Shape not found.\n";
        return *it->get();
    }

    [[nodiscard]] const std::vector<std::unique_ptr<sf::Shape>>& ShapeComposite::getShapes() const {
        return shapes;
    };

    RenderComponent::RenderComponent(Entity &entity):entity(entity) {}

    const std::vector<std::unique_ptr<ShapeComposite>> & RenderComponent::getShapeComposites() const {
        return composites;
    }

    void RenderComponent::stretchToWidth(sf::RectangleShape *pShape) const {
        pShape->setSize({
            3*static_cast<float>(entity.game.video.getWindow().getSize().x),
            pShape->getSize().y
            }
        );
    }

    void RenderComponent::repeatToWidth(sf::RectangleShape *pShape) const {
        stretchToWidth(pShape);
        const int texWidth = static_cast<int>(pShape->getTexture()->getSize().x);
        const int texHeight = static_cast<int>(pShape->getTexture()->getSize().y);
        const int shapeWidth = static_cast<int>(pShape->getGlobalBounds().size.x);
        pShape->setTextureRect(
            sf::IntRect({0, 0}, {std::max(3*texWidth, shapeWidth), texHeight}));
    }

    void RenderComponent::addComposite(std::unique_ptr<ShapeComposite> composite) {
        composites.push_back(std::move(composite));
    }

    void RenderComponent::setFillColor(const sf::Color &color) const {
        for (const auto &pComposite : composites) {
            for (const auto &pShape : pComposite->getShapes()) {
                pShape->setFillColor(color);
            }
        }
    }

    ShapeComposite & RenderComponent::getShapeComposite(const ShapeComposite &composite) {
        const auto it = std::ranges::find_if(
            composites,
            [&composite](const std::unique_ptr<ShapeComposite>& obj) {
                return obj.get() == &composite;
            });
        if (it == composites.end()) std::cout << "Composite not found.\n";
        return *it->get();
    }

    void RenderComponent::update() const {
        for (const auto &pComposite : composites) {
            pComposite->setPosition(entity.position);
        }
    }
} // entity