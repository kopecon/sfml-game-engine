//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_WORLD_HPP
#define BONK_GAME_WORLD_HPP
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <memory>
#include "../../Utils/utils.hpp"
#include "../Entity/Entity.hpp"


class Game;

class World {
    entityID newEntityID{0};
protected:
    // ENTITIES
    std::unordered_map<entityID, std::unique_ptr<Entity>> entities{};
public:
    #pragma region constructors
    explicit World(Game &game, std::string name);
    #pragma endregion constructors
    // REFERENCES  //TODO: Should reference be const?
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
    T* createEntity(Args&&... args)
    requires (std::is_base_of_v<Entity, T>) {
        // Create entity
        auto pEntity = std::make_unique<T>(*this, ++newEntityID, std::forward<Args>(args)...);
        // Init entity
        pEntity->init();
        // Store in the list of entities
        auto [it, inserted] = entities.emplace(pEntity->getID(), std::move(pEntity));
        return getEntity<T>(*it->second.get());
    }

    // Create Entity at a defined position
    template<typename T, typename ... Args>
    T* createEntity(sf::Vector2f position, Args&&... args)
    requires (std::is_base_of_v<Entity, T>) {
        // Create the entity
        auto pEntity = std::make_unique<T>(*this, ++newEntityID, std::forward<Args>(args)...);
        // Init the entity
        pEntity->init();
        pEntity->shape.setPosition(position);
        // Get its name
        // Store in the list of entities
        auto [it, inserted] = entities.emplace(pEntity->getID(), std::move(pEntity));
        return getEntity<T>(*it->second.get());
    }

    template<typename T>
    T* getEntity(const Entity &entity)
    requires (std::is_base_of_v<Entity, T>) {
        const auto it = entities.find(entity.getID());
        if (it == entities.end()) return nullptr;
        return dynamic_cast<T*>(it->second.get());
    }

    std::unordered_map<entityID, std::unique_ptr<Entity>>* getEntities() {
        return &entities;
    }

    template<typename T>
    std::vector<T *> findEntities() const
    requires (std::is_base_of_v<Entity, T>) {
        std::vector<T*> entitiesOfType{};
        for (auto &entity: entities | std::views::values) {
            if (auto it = dynamic_cast<T*>(entity.get())) {
                entitiesOfType.emplace(entitiesOfType.end(), it);
            }
        }
        return entitiesOfType;
    }

    void remove(const Entity &entity) {
        const auto it = entities.find(entity.getID());
        entities.erase(it);
    }

    void printEntities() {
        for (auto const &entity : entities | std::views::values) {
            std::cout << entity->getID() << " ";
        }
        std::cout << "\n";
    }

    void update();
};
#endif //BONK_GAME_WORLD_HPP