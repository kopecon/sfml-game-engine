#include "EntityManager/Entity/Components/ColliderComponent.hpp"

#include "Engine.hpp"
#include "EntityManager/EntityManager.hpp"
#include "EntityManager/Entity/Entity.hpp"


namespace entity {
    RectangleCollider::RectangleCollider(const sf::Vector2f size) : RectangleShape(size) {
        auto magenta = sf::Color::Magenta;
        magenta.a = 16.f; // 6% transparent
        rectangleShape_->setFillColor(magenta);
        rectangleShape_->setOutlineColor(sf::Color::Magenta);
        rectangleShape_->setOutlineThickness(1.f);
    }

    ColliderComponent::ColliderComponent(Entity &owner)
        : owner_(owner),
          hitbox_(owner_.size()) {
        update();
    }

    void ColliderComponent::setHitMap(render::HitMap &&map) const noexcept {
        hitMap_.emplace(std::move(map));
    }

    void ColliderComponent::setVisible() noexcept {
        visible_ = true;
    }

    const RectangleCollider &ColliderComponent::hitbox() const noexcept {
        return hitbox_;
    }

    std::optional<Collision> ColliderComponent::collidesWith(const ColliderComponent &other) const noexcept {
        return AABB(other);
    }

    Collisions ColliderComponent::checkForCollisionsWith(const EntitiesWeak &entities) const noexcept {
        Collisions collisions{};
        for (const auto &entity_weak: entities | std::views::values) {
            if (!entity_weak.lock()) return collisions;

            auto &entity = *entity_weak.lock();

            if (entity == owner_ or !entity.has<ColliderComponent>()) continue;

            auto collision = collidesWith(entity.collider());

            if (collision.has_value()) {
                collision.value().entity = entity_weak;

                auto overlaps = checkHit(entity);

                if (overlaps.has_value()) {
                    collision.value().hits = overlaps.value();
                }

                collisions.emplace(entity.instance_id(), std::move(collision.value()));
            }
        }
        return collisions;
    }

    Collisions ColliderComponent::checkForCollisions() const noexcept {
        return checkForCollisionsWith(owner_.engine.currentScene().findAll());
    }

    void ColliderComponent::update() const noexcept {
        if (hitMap_.has_value()) {
            alignWithHitMap();
        } else if (owner_.has<RenderComponent>()) {
            alignWithRender();
        }
    }

    void ColliderComponent::alignWithHitMap() const noexcept {
        // Issue: hit map bounds don't share the owners position on the first frame
        hitMap_->update();
        const auto &hb = hitMap_->getHitMapBounds();
        hitbox_.setPosition(hb.position);
        hitbox_.setSize(hb.size);
    }

    void ColliderComponent::alignWithRender() const noexcept {
        auto &render = owner_.render();
        render.setPosition(owner_.position());
        hitbox_.setPosition(render.getGlobalBounds().position);
        hitbox_.setSize(render.getGlobalBounds().size);
    }

    std::optional<Collision> ColliderComponent::AABB(const ColliderComponent &other) const noexcept {
        Collision collision{};

        update();
        other.update();

        // CALCULATIONS ARE FROM THE PERSPECTIVE OF THIS
        const auto thisBounds = hitbox_.getGlobalBounds();
        const auto otherBounds = other.hitbox_.getGlobalBounds();

        const auto thisPos = thisBounds.position;
        const auto otherPos = otherBounds.position;
        const auto thisSize = thisBounds.size;
        const auto otherSize = otherBounds.size;

        const auto thisTop = thisPos.y;
        const auto otherTop = otherPos.y;
        const auto thisBottom = thisTop + thisSize.y;
        const auto otherBottom = otherTop + otherSize.y;

        const auto thisLeft = thisPos.x;
        const auto otherLeft = otherPos.x;
        const auto thisRight = thisLeft + thisSize.x;
        const auto otherRight = otherLeft + otherSize.x;

        // HOW MUCH THIS PENETRATES OTHER
        auto topPen = otherTop - thisBottom;
        auto bottomPen = otherBottom - thisTop;

        auto leftPen = otherLeft - thisRight;
        auto rightPen = otherRight - thisLeft;

        const bool isAbove = topPen > 0.f;
        const bool isBellow = bottomPen < 0.f;

        const bool isLeft = leftPen > 0.f;
        const bool isRight = rightPen < 0.f;

        if (isAbove or isBellow or isLeft or isRight) {
            return std::nullopt;
        }

        topPen = std::abs(topPen);
        bottomPen = std::abs(bottomPen);
        leftPen = std::abs(leftPen);
        rightPen = std::abs(rightPen);

        const auto minPD = std::min(std::min(topPen, bottomPen), std::min(leftPen, rightPen)
        );

        if (minPD == topPen) {
            collision.depth = {0.f, -minPD};
        } else if (minPD == bottomPen) {
            collision.depth = {0.f, minPD};
        } else if (minPD == leftPen) {
            collision.depth = {-minPD, 0.f};
        } else if (minPD == rightPen) {
            collision.depth = {minPD, 0.f};
        }

        return collision;
    }

    std::optional<render::HitMap::Overlap> ColliderComponent::checkHit(const Entity &entity) const noexcept {
        if (hitMap_.has_value() && entity.collider().hitMap_.has_value()) {
            return hitMap_.value().getOverlap(entity.collider().hitMap_.value());
        }
        return std::nullopt;
    }
}
