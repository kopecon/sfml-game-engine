#include "Video/SceneGraph/RectangleShape.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "math.hpp"
#include "utils.hpp"


namespace render {
    RectangleShape::RectangleShape() : rectangleShape_(std::make_unique<sf::RectangleShape>()) {
    }

    RectangleShape::RectangleShape(const sf::Vector2f &size) : rectangleShape_(
        std::make_unique<sf::RectangleShape>(size)) {
        RectangleShape::updateNormals();
    }

    Colorable *RectangleShape::asColorable() noexcept {
        return this;
    }

    void RectangleShape::applyColor(const sf::Color color) noexcept {
        rectangleShape_->setFillColor(color);
    }

    void RectangleShape::setSize(const sf::Vector2f size) const noexcept {
        rectangleShape_->setSize(size);
    }

    sf::Transformable & RectangleShape::kernel() noexcept {
        return *rectangleShape_;
    }

    const sf::Transformable & RectangleShape::kernel() const noexcept {
        return *rectangleShape_;
    }

    inline void RectangleShape::drawSelf(sf::RenderTarget &target, const sf::RenderStates states) const noexcept {
        target.draw(*rectangleShape_, states);
    }

    std::optional<sf::FloatRect> RectangleShape::getSelfGlobalBounds() const noexcept {
        return rectangleShape_->getLocalBounds();
    }

    void RectangleShape::updateNormals() noexcept {
        auto p0 = rectangleShape_->getPoint(0);
        auto p1 = rectangleShape_->getPoint(1);
        auto p3 = rectangleShape_->getPoint(3);

        const auto transform = getTransform();
        p0 = transform.transformPoint(p0);
        p1 = transform.transformPoint(p1);
        p3 = transform.transformPoint(p3);

        sf::Vector2f tangent1 = p0 - p3;
        sf::Vector2f tangent2 = p0 - p1;

        const unsigned length1 = std::sqrt(tangent1.x * tangent1.x + tangent1.y * tangent1.y);
        const unsigned length2 = std::sqrt(tangent2.x * tangent2.x + tangent2.y * tangent2.y);

        // Normalize to length 1
        tangent1.x = tangent1.x / length1;
        tangent1.y = tangent1.y / length1;
        tangent2.x = tangent2.x / length2;
        tangent2.y = tangent2.y / length2;

        const sf::Vector2f normal1 = {-tangent1.y, tangent1.x};
        const sf::Vector2f normal2 = {-tangent2.y, tangent2.x};

        normals_ = {{normal1}, {normal2}};
    }
} // render
