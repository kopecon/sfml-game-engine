#pragma once

#include <deque>
#include <ranges>


#include "Entity/Entity.hpp"
#include "StateMachine/Actor/Actor.hpp"


class EntityManager {
    friend Engine;

    template<IsEntity T>
    class EntityBuilder {
    public:
        // ReSharper disable once CppNonExplicitConvertingConstructor
        EntityBuilder(std::weak_ptr<T> entity); // NOLINT(*-explicit-constructor)

        EntityBuilder &&at(sf::Vector2f pos) && {
            if (auto shared = entity_.lock()) {
                shared->position() = pos;
            }
            return std::move(*this);
        }

        template<IsActor NPCType, typename... Args>
        EntityBuilder &&asNPC(Args &&... args) && {
            auto sharedEntity = entity_.lock();

            if (!sharedEntity) { return std::move(*this); }

            auto npcWeak = sharedEntity->engine.currentScene().template make<NPCType>(std::forward<Args>(args)...);

            if (auto npcShared = npcWeak.lock()) {
                npcShared->posses(std::weak_ptr<T>(entity_));
            }
            return std::move(*this);
        }

        [[nodiscard]] std::weak_ptr<T> get() && { return std::move(entity_); }

        explicit operator std::weak_ptr<T>() && { return std::move(entity_); }
        T *operator->() const { return entity_.lock().get(); }
        T &operator*() const { return *entity_.lock(); }

    private:
        std::weak_ptr<T> entity_{};
    };

public:
    virtual ~EntityManager() = default;

    explicit EntityManager(Engine &engine);

    // REFERENCES
    const Engine &engine;

    template<IsActor T>
    std::weak_ptr<T> add(std::unique_ptr<T> actor) const noexcept {
        std::shared_ptr entry = std::move(actor);
        std::weak_ptr ptr = entry;
        actorAddQue_.emplace_back(std::move(entry));
        return ptr;
    }

    template<IsEntity T>
    std::weak_ptr<T> add(std::unique_ptr<T> entity) const noexcept {
        std::shared_ptr entry = std::move(entity);
        std::weak_ptr ptr = entry;
        entityAddQue_.emplace_back(std::move(entry));
        return ptr;
    }

    template<IsActor T, typename... Args>
    std::weak_ptr<T> make(Args &&... args) const noexcept {
        auto newActor = std::make_unique<T>(engine, std::forward<Args>(args)...);
        return add(std::move(newActor));
    }

    template<IsEntity T, typename... Args>
    EntityBuilder<T> make(Args &&... args) const noexcept {
        auto newEntity = std::make_unique<T>(engine, std::forward<Args>(args)...);
        return add(std::move(newEntity));
    }

    // GETTERS
    template<IsEntity T = Entity>
    [[nodiscard]] std::weak_ptr<T> findFirst() const noexcept {
        const auto entities = entities_ | std::views::values;
        const auto it = std::ranges::find_if(
            entities,
            [](const auto &pEntity) { return pEntity->template is<T>(); }
        );

        if (it != entities.end()) {
            return std::static_pointer_cast<T>(*it);
        }

        return {};
    }

    template<IsEntity T = Entity>
    [[nodiscard]] EntitiesWeak findAll() const noexcept {
        return entities_ | std::views::filter(
                   [](const auto &pair) { return pair.second->template is<T>(); }
               ) | std::ranges::to<EntitiesWeak>();
    }

    template<IsEntity T = Entity>
    [[nodiscard]] std::weak_ptr<T> get(const InstanceID<Entity> &id) const noexcept {
        const auto it = entities_.find(id);

        if (it == entities_.end()) {
            LOG_WARN("World does not contain id.", true);
            return {};
        }

        const auto &target = it->second;

        if (!target->is<T>()) {
            LOG_WARN("Found target is not expected type.", true);
            return {};
        }

        return std::static_pointer_cast<T>(target);
    }

    template<IsEntity T = Entity>
    [[nodiscard]] std::weak_ptr<T> get(const sf::Vector2f pos) const noexcept {
        for (const auto &[key, entity]: entities_ | std::views::reverse) {
            if (!entity->has<entity::RenderComponent>()) continue;
            if (entity->render().contains(pos)) {
                return get<T>(key);
            }
        }
        LOG_WARN("No entity on given position.", true);
        return {};
    }

protected:
    Actors actors_{};
    Entities entities_{};

private:
    mutable std::deque<std::shared_ptr<Actor> > actorAddQue_{};
    mutable std::deque<std::shared_ptr<Entity> > entityAddQue_{};

    // UPDATE
    void update();
};

template<IsEntity T>
EntityManager::EntityBuilder<T>::EntityBuilder(std::weak_ptr<T> entity): entity_(std::move(entity)) {
}
