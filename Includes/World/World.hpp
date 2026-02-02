//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_WORLD_HPP
#define BONK_GAME_WORLD_HPP
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "../Entity/Entity.hpp"
#include "../Entity/Player/Player.hpp"


class Game;

class World {
    entityID newEntityID{0};
protected:
    // ENTITIES
    std::unordered_map<entityID, std::unique_ptr<entity::Entity>> entities{};
    // COUNTER
    std::unordered_map<std::type_index, std::size_t> entityCounter{};
public:
    #pragma region constructors
    explicit World(Game &game, std::string name);
    #pragma endregion constructors

    // REFERENCES
    Game &game;
    // METADATA
    const std::string name{};
    // ENVIRONMENT CHARACTERISTIC
    const float gravity = 10000;
    const float airFriction = 0.f;
    const float groundFriction = 1.f;
    const float groundLevel{};

    // Create Entity at [0, 0]
    template<typename T, typename ... Args>
    requires (std::is_base_of_v<entity::Entity, T>)
    T& createEntity(Args&&... args) {
        // Count entity
        entityCounter[typeid(T)] += 1;
        auto entityName = T::getClassName() + std::to_string(getEntityCount(typeid(T)));
        // Create entity
        auto entity = std::make_unique<T>(*this, ++newEntityID, entityName, std::forward<Args>(args)...);
        T& entityRef = *entity;
        // Store in the list of entities
        entities.emplace(entity->getID(), std::move(entity));
        std::cout << entityName << " created. \n";
        return entityRef;
    }

    // Create Entity at [x,y]
    template<typename T, typename ... Args>
    requires (std::is_base_of_v<entity::Entity, T>)
    T& createEntityAt(sf::Vector2f position, Args&&... args) {
        // Create the entity
        T& entity = createEntity<T>(args...);
        entity.position = position;
        return entity;
    }

    template<typename T>
    std::vector<T*> getEntities() const
    requires (std::is_base_of_v<entity::Entity, T>)
    {
        std::vector<T*> entitiesOfType{};
        for (auto &pEntity: entities | std::views::values) {
            if (auto it = dynamic_cast<T*>(pEntity.get())) {
                entitiesOfType.emplace(entitiesOfType.end(), it);
            }
        }
        return entitiesOfType;
    }

    void remove(const entity::Entity &entity) {
        const auto it = entities.find(entity.getID());
        entities.erase(it);
    }

    void printEntities() {
        for (auto const &entity : entities | std::views::values) {
            std::cout << entity->getID() << " ";
        }
        std::cout << "\n";
    }

    std::unordered_map<entityID, std::unique_ptr<entity::Entity>>* getEntities() {
        return &entities;
    }

    [[nodiscard]] std::size_t getEntityCount(const std::type_info &entityInfo) const {
        return entityCounter.at(entityInfo);
    }

    void update();
};
#endif //BONK_GAME_WORLD_HPP