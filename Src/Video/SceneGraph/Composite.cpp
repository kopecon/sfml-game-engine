#include "Video/SceneGraph/Composite.hpp"

#include <ranges>

#include <SFML/Graphics/RenderTarget.hpp>

#include "math.hpp"
#include "Video/Animation/Animatable.hpp"
#include "Video/SceneGraph/Colorable.hpp"


namespace render {
#pragma region constructors
    Composite::Outline::Outline(const sf::FloatRect bounds) {
        setSize(bounds.size);
        setPosition(bounds.position);
        setFillColor(sf::Color::Transparent);
        setOutlineColor(sf::Color::Red);
        setOutlineThickness(1.f);
    }

    Composite::Composite() = default;

    Composite::Composite(Composite &&other) noexcept
        : Transformable(other),
          visible(other.visible),
          children_(std::move(other.children_)),
          normals_(std::move(other.normals_)),
          outline_(std::move(other.outline_)),
          parent_(other.parent_) {
        for (const auto &child: getChildren() | std::views::values) {
            child->parent_ = this;
        }
    }

    Composite &Composite::operator=(Composite &&other) noexcept {
        if (this != &other) {
            Transformable::operator=(other);
            visible = other.visible;
            children_ = std::move(other.children_);
            normals_ = std::move(other.normals_);
            outline_ = std::move(other.outline_);
            parent_ = other.parent_;

            for (const auto &child: getChildren() | std::views::values) {
                child->parent_ = this;
            }
        }
        return *this;
    }

#pragma endregion

    void Composite::play(const float dt) noexcept {
        // Own animation
        if (const auto animated = asAnimatable()) {
            animated->animate(dt);
        }
        // Children animation
        for (const auto &child: children_ | std::views::values) {
            child->play(dt);
        }
    }

    void Composite::draw(sf::RenderTarget &target, sf::RenderStates states) const noexcept {
        if (visible) {
            states.transform *= getTransform(); // PROPAGATE TRANSFORM
            drawSelf(target, states);
            drawChildren(target, states);
            drawOutline(target, states);
        }
    }

    void Composite::recolor(const sf::Color &color) noexcept {
        // Color self
        if (const auto colorable = asColorable()) {
            colorable->applyColor(color);
        }
        // Color children
        for (const auto &child: getChildren() | std::views::values) {
            if (const auto colorable = child->asColorable()) {
                colorable->applyColor(color);
            }
        }
    }

    void Composite::resize(const sf::Vector2f targetSize) noexcept {
        const auto originalSize = getGlobalBounds().size;

        const auto scale2D = utils::math::hd::divide(targetSize, originalSize);

        setScale({scale2D.x, scale2D.y});
    }

    void Composite::fit(const sf::Vector2f size) noexcept {
        const auto originalSize = getGlobalBounds().size;

        const auto scale2D = utils::math::hd::divide(size, originalSize);

        float scale = std::min(scale2D.x, scale2D.y);

        setScale({scale, scale});
    }

    void Composite::cover(const sf::Vector2f size) noexcept {
        const auto originalSize = getGlobalBounds().size;

        const auto scale2D = utils::math::hd::divide(size, originalSize);

        float scale = std::max(scale2D.x, scale2D.y);

        setScale({scale, scale});
    }

    void Composite::showOutline(const sf::Color color) const noexcept {
        outline_->setOutlineColor(color);
        outline_->visible = true;
    }

    void Composite::toggleOutline() const noexcept {
        outline_->visible = !outline_->visible;
    }

    Animatable *Composite::asAnimatable() noexcept {
        return nullptr;
    }

    Colorable *Composite::asColorable() noexcept {
        return nullptr;
    }

    sf::FloatRect Composite::getLocalBounds() const noexcept {
        bool initialized = false;

        sf::Vector2f minPos;
        sf::Vector2f maxSize;

        auto absorb = [&](const sf::FloatRect &bounds) {
            const sf::Vector2f childMinPos = bounds.position;
            const sf::Vector2f childMaxSize = bounds.position + bounds.size;

            if (!initialized) {
                minPos = childMinPos;
                maxSize = childMaxSize;
                initialized = true;
            } else {
                minPos.x = std::min(minPos.x, childMinPos.x);
                minPos.y = std::min(minPos.y, childMinPos.y);
                maxSize.x = std::max(maxSize.x, childMaxSize.x);
                maxSize.y = std::max(maxSize.y, childMaxSize.y);
            }
        };

        if (const auto selfBounds = getSelfGlobalBounds()) {
            absorb(*selfBounds);
        }

        for (const auto &child: children_ | std::views::values) {
            absorb(child->getTransform().transformRect(child->getLocalBounds()));
        }

        if (!initialized)
            return {};

        return {minPos, maxSize - minPos};
    }

    sf::FloatRect Composite::getGlobalBounds() const noexcept {
        return getGlobalTransform().transformRect(getLocalBounds());
    }

    sf::Transform Composite::getGlobalTransform() const noexcept {
        sf::Transform t = sf::Transform::Identity;

        auto current = this;

        while (current) {
            t = current->getTransform() * t;
            current = current->parent_;
        }

        return t;
    }

    sf::Vector2f Composite::getCenter() const noexcept {
        const auto bounds = getLocalBounds();
        const auto x = bounds.position.x + bounds.size.x / 2.f;
        const auto y = bounds.position.y + bounds.size.y / 2.f;
        return {x, y};
    }

    id::OMap<Composite, std::unique_ptr<Composite> > &Composite::getChildren() noexcept {
        return children_;
    }

    bool Composite::contains(const sf::Vector2f pos) const noexcept {
        if (getGlobalBounds().contains(pos)) {
            return true;
        }
        return false;
    }

    std::vector<sf::Vector2f> Composite::getNormals() noexcept {
        updateNormals(); // For better performance, we should update normals only when needed. For now this is ok.
        return normals_;
    }

    sf::Transformable &Composite::kernel() noexcept {
        assert(false && "This composite does not have root.");
        std::unreachable();
    }

    const sf::Transformable &Composite::kernel() const noexcept {
        assert(false && "This composite does not have root.");
        std::unreachable();
    }

    float Composite::circumcircleRadius() const noexcept {
        const auto size = getGlobalBounds().size;
        return std::max(size.x, size.y);
    }

    std::optional<sf::FloatRect> Composite::getSelfGlobalBounds() const noexcept {
        return std::nullopt;
    }

    void Composite::drawChildren(sf::RenderTarget &target, const sf::RenderStates states) const noexcept {
        for (const auto &child: children_ | std::views::values) {
            target.draw(*child, states);
        }
    }

    void Composite::drawOutline(sf::RenderTarget &target, const sf::RenderStates states) const noexcept {
        if (!outline_->visible && !Outline::visibleAll) return;

        const sf::FloatRect newBounds = states.transform.transformRect(getLocalBounds());
        outline_->setSize(newBounds.size);
        outline_->setPosition(newBounds.position);
        target.draw(*outline_);
    }

    void Composite::updateNormals() noexcept {
    }
} // render
