#ifndef BONK_GAME_WORLD_HPP
#define BONK_GAME_WORLD_HPP

#include <iostream>
#include <ranges>
#include <typeindex>
#include "Game/World/Entity/Entity.hpp"

class Game;


class World {
public:
#pragma region constructors
    explicit World(Game &game, std::string name);
#pragma endregion constructors

    // REFERENCES
    const Game &game;

    // ENVIRONMENT CHARACTERISTIC
    const float gravity = 10000;
    const float airFriction = 0.f;
    const float groundFriction = 1.f;
    const float groundLevel{};
    // SETTERS
    // Create Entity at [0, 0]
    template<typename T, typename... Args>
        requires (std::is_base_of_v<entity::Entity, T>)
    T &createEntity(Args &&... args) {
        // Count entity
        entityCounter_[typeid(T)] += 1;
        auto entityName = T::getClassName() + std::to_string(getEntityCount(typeid(T)));
        // Create entity
        auto entity = std::make_unique<T>(*this, ++newEntityID_, entityName, std::forward<Args>(args)...);
        T &entityRef = *entity;
        // Store in the list of entities
        entities_.emplace(entity->getID(), std::move(entity));
        std::cout << entityName << " created. \n";
        return entityRef;
    }

    // Create Entity at [x,y]
    template<typename T, typename... Args>
        requires (std::is_base_of_v<entity::Entity, T>)
    T &createEntityAt(sf::Vector2f position, Args &&... args) {
        // Create the entity
        T &entity = createEntity<T>(args...);
        entity.physics().properties().position = position;
        return entity;
    }

    void remove(const entity::Entity &entity) {
        const auto it = entities_.find(entity.getID());
        entities_.erase(it);
    }

    // GETTERS
    template<typename T>
    [[nodiscard]] std::vector<T *> getEntities() const
        requires (std::is_base_of_v<entity::Entity, T>) {
        std::vector<T *> entitiesOfType{};
        for (auto &pEntity: entities_ | std::views::values) {
            if (auto it = dynamic_cast<T *>(pEntity.get())) {
                entitiesOfType.emplace(entitiesOfType.end(), it);
            }
        }
        return entitiesOfType;
        }

    [[nodiscard]] std::unordered_map<entityID, std::unique_ptr<entity::Entity> > *getEntities() {
        return &entities_;
    }

    [[nodiscard]] std::size_t getEntityCount(const std::type_info &entityInfo) const {
        return entityCounter_.at(entityInfo);
    }

    [[nodiscard]] std::string getName() const;

    // UPDATE
    void update();

    // DEBUG
    void printEntities() {
        for (auto const &entity: entities_ | std::views::values) {
            std::cout << entity->getID() << " ";
        }
        std::cout << "\n";
    }

private:
    // METADATA
    entityID newEntityID_{0};
    const std::string name_{};

protected:
    // ENTITIES
    std::unordered_map<entityID, std::unique_ptr<entity::Entity> > entities_{};
    // COUNTER
    std::unordered_map<std::type_index, std::size_t> entityCounter_{};
};
#endif //BONK_GAME_WORLD_HPP
