#pragma once

#include <optional>

#include "utils.hpp"
#include "EntityManager/Entity/Components/ColliderComponent.hpp"
#include "EntityManager/Entity/Components/PhysicsComponent.hpp"
#include "EntityManager/Entity/Components/RenderComponent.hpp"
#include "Identification/Identities.hpp"
#include "Identification/Maps.hpp"


class EntityManager;
class Engine;


namespace entity {
    struct StatComponent {
        float eyeDryness{0.f}; // temporary... move to player
    };

    class Entity : public id::Node<Entity> {
        friend ColliderComponent;
        friend EntityManager;

    public:
        ~Entity() override;

        explicit Entity(const Engine &engine);

        const Engine &engine;

        void enablePhysics() noexcept;

#pragma region Getters
        // GETTERS
        template<typename T>
        [[nodiscard]] bool has() const {
            if constexpr (std::is_same_v<T, PhysicsComponent>) return physics_.has_value();
            else if constexpr (std::is_same_v<T, RenderComponent>) return render_.has_value();
            else if constexpr (std::is_same_v<T, StatComponent>) return static_cast<bool>(stats_);
            else if constexpr (std::is_same_v<T, ColliderComponent>) return collider_.has_value();
            else static_assert(utils::always_false_v<T>, "Entity does not support this component type!");
            return false;
        }

        [[nodiscard]] StatComponent &properties() noexcept;

        [[nodiscard]] const StatComponent &properties() const noexcept;

        [[nodiscard]] PhysicsComponent &physics() noexcept;

        [[nodiscard]] const PhysicsComponent &physics() const noexcept;

        [[nodiscard]] RenderComponent &render() noexcept;

        [[nodiscard]] const RenderComponent &render() const noexcept;

        [[nodiscard]] ColliderComponent &collider() noexcept;

        [[nodiscard]] const ColliderComponent &collider() const noexcept;

        [[nodiscard]] sf::Vector2f &position() noexcept;

        [[nodiscard]] const sf::Vector2f &position() const noexcept;

        [[nodiscard]] sf::Vector2f &size() noexcept;

        [[nodiscard]] const sf::Vector2f &size() const noexcept;

        [[nodiscard]] InstanceID<Entity> id() const noexcept;
#pragma endregion

    protected:
        void setRender(RenderComponent &&render) noexcept;

        void setCollider(ColliderComponent &&collider) noexcept;

        virtual void setupRender() noexcept;

        virtual void setupCollider() noexcept;

        // UPDATES
        virtual void onUpdate() noexcept = 0;

    private:
        bool markedForRemoval_{false};
        sf::Vector2f position_{0.f, 0.f};
        sf::Vector2f size_{0.f, 0.f};
        // identity::InstanceOMap<Entity, std::shared_ptr<Entity> > children_{};

        // COMPONENTS
        std::unique_ptr<StatComponent> stats_{std::make_unique<StatComponent>()};
        std::optional<PhysicsComponent> physics_{std::nullopt};
        std::optional<RenderComponent> render_{std::nullopt};
        std::optional<ColliderComponent> collider_{std::nullopt};

        friend void markForRemoval(Entity &entity) noexcept;

        void update() noexcept;
    };
}


inline void entity::markForRemoval(Entity &entity) noexcept {
    entity.markedForRemoval_ = true;
}


template<typename T>
concept IsEntity = std::derived_from<T, entity::Entity>;


template<typename T>
using EntitySubtype = id::Node<T, entity::Entity>;

using Entity = entity::Entity;

using Entities = id::InstanceOMap<entity::Entity, std::shared_ptr<entity::Entity> >;
using EntitiesWeak = id::InstanceOMap<entity::Entity, std::weak_ptr<entity::Entity> >;
