#include "EntityManager/Entity/Entity.hpp"


namespace entity {
    Entity::~Entity() {
        std::cout << *this << " deleted. \n";
    }

    Entity::Entity(const Engine &engine)
        : engine(engine) {
    }

    void Entity::enablePhysics() noexcept {
        physics_.emplace(PhysicsComponent{*this});
    }

    StatComponent &Entity::properties() noexcept {
        assert(stats_ && "Trying to access unavailable stats!");
        return *stats_;
    }

    const StatComponent &Entity::properties() const noexcept {
        assert(stats_ && "Trying to access unavailable stats!");
        return *stats_;
    }

    PhysicsComponent &Entity::physics() noexcept {
        assert(physics_.has_value() && "Trying to access unavailable physics!");
        return physics_.value();
    }

    const PhysicsComponent &Entity::physics() const noexcept {
        assert(physics_.has_value() && "Trying to access unavailable physics!");
        return physics_.value();
    }

    RenderComponent &Entity::render() noexcept {
        assert(render_.has_value() && "Trying to access unavailable render!");
        return render_.value();
    }

    const RenderComponent &Entity::render() const noexcept {
        assert(render_.has_value() && "Trying to access unavailable render!");
        return render_.value();
    }

    ColliderComponent &Entity::collider() noexcept {
        assert(collider_.has_value() && "Trying to access unavailable collider!");
        return collider_.value();
    }

    const ColliderComponent &Entity::collider() const noexcept {
        assert(collider_.has_value() && "Trying to access unavailable collider!");
        return collider_.value();
    }

    sf::Vector2f &Entity::position() noexcept {
        return position_;
    }

    const sf::Vector2f &Entity::position() const noexcept {
        return position_;
    }

    sf::Vector2f &Entity::size() noexcept {
        return size_;
    }

    const sf::Vector2f &Entity::size() const noexcept {
        return size_;
    }

    InstanceID<Entity> Entity::id() const noexcept {
        return instance_id();
    }

    void Entity::setRender(RenderComponent &&render) noexcept {
        render_.emplace(std::move(render));
    }

    void Entity::setCollider(ColliderComponent &&collider) noexcept {
        collider_.emplace(std::move(collider));
    }

    void Entity::setupRender() noexcept {
    }

    void Entity::setupCollider() noexcept {
        ColliderComponent collider{*this};
        collider.isSolid = true;
        setCollider(std::move(collider));
    }

    void Entity::update() noexcept {
        onUpdate();
        if (physics_.has_value()) {
            physics().update();
        }
    }
}
