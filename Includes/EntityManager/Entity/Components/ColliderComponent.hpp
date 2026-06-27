#pragma once

#include "Identification/Identities.hpp"
#include "Video/SceneGraph/HitMap.hpp"
#include "Video/SceneGraph/RectangleShape.hpp"


class VideoComponent;


namespace entity {
    class Entity;

    struct Collision {
        std::weak_ptr<Entity> entity{};
        sf::Vector2f depth{0.f, 0.f};
        render::HitMap::Overlap hits{};
    };

    using Collisions = id::InstanceUMap<Entity, Collision>;

    class RectangleCollider : public render::RectangleShape {
    public:
        RectangleCollider() = default;

        explicit RectangleCollider(sf::Vector2f size);
    };

    class ColliderComponent {
        using Entities = id::InstanceOMap<Entity, std::shared_ptr<Entity> >;
        using EntitiesWeak = id::InstanceOMap<Entity, std::weak_ptr<Entity> >;
        friend VideoComponent;

    public:
        explicit ColliderComponent(Entity &owner);

        void setHitMap(render::HitMap &&map) const noexcept;

        void setVisible() noexcept;

        [[nodiscard]] const RectangleCollider &hitbox() const noexcept;

        [[nodiscard]] std::optional<Collision> collidesWith(const ColliderComponent &other) const noexcept;

        [[nodiscard]] Collisions checkForCollisionsWith(const EntitiesWeak &entities) const noexcept;

        [[nodiscard]] Collisions checkForCollisions() const noexcept;

        void update() const noexcept;

        bool isSolid{false};

    private:
        Entity &owner_;
        // Mutable should be just a temporary shortcut
        mutable RectangleCollider hitbox_{}; // Mutable so that can be updated with const getter
        mutable std::optional<render::HitMap> hitMap_{}; // Mutable so that can be updated with const getter
        bool visible_{false}; // Sets visibility for this instance.
        static constexpr bool visibleAll_{false}; // Sets visibility for every collider object.

        void alignWithHitMap() const noexcept;

        void alignWithRender() const noexcept;

        // Axis-Aligned Bounding Box algorythm for collision detection
        std::optional<Collision> AABB(const ColliderComponent &other) const noexcept;

        std::optional<render::HitMap::Overlap> checkHit(const Entity &entity) const noexcept;
    };
}
