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

#include "../../Utils/utils.hpp"
#include "../Entity/Entity.hpp"


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
    T& createEntity(Args&&... args)
    requires (std::is_base_of_v<entity::Entity, T>) {
        // Create entity
        auto pEntity = std::make_unique<T>(*this, ++newEntityID, std::forward<Args>(args)...);
        // Init entity
        pEntity->init();
        // Count entity
        entityCounter[typeid(*pEntity)] += 1;
        // Store in the list of entities
        auto [it, inserted] = entities.emplace(pEntity->getID(), std::move(pEntity));
        return getEntity<T>(*it->second.get());
    }

    // Create Entity at a defined position
    template<typename T, typename ... Args>
    T& createEntity(sf::Vector2f position, Args&&... args)
    requires (std::is_base_of_v<entity::Entity, T>) {
        // Create the entity
        auto pEntity = std::make_unique<T>(*this, ++newEntityID, std::forward<Args>(args)...);
        // Init the entity
        pEntity->init();
        pEntity->getShape()->setPosition(position);
        // Count entity
        entityCounter[typeid(*pEntity)] += 1;
        // Store in the list of entities
        auto [it, inserted] = entities.emplace(pEntity->getID(), std::move(pEntity));
        return getEntity<T>(*it->second.get());
    }

    template<typename T>
    std::vector<T&> findEntities() const
    requires (std::is_base_of_v<entity::Entity, T>) {
        std::vector<T&> entitiesOfType{};
        for (auto &entity: entities | std::views::values) {
            if (auto it = dynamic_cast<T&>(entity.get())) {
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

    template<typename T>
    T& getEntity(const entity::Entity &entity)
    requires (std::is_base_of_v<entity::Entity, T>) {
        const auto it = entities.find(entity.getID());
        return dynamic_cast<T&>(*it->second);
    }

    std::unordered_map<entityID, std::unique_ptr<entity::Entity>>* getEntities() {
        return &entities;
    }

    std::size_t getEntityCount(const entity::Entity &entity) {
        return entityCounter[typeid(entity)];
    }

    void update();
};
#endif //BONK_GAME_WORLD_HPP