//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_WORLD_HPP
#define BONK_GAME_WORLD_HPP
#include <ranges>
#include <unordered_map>
#include <memory>
#include "../../Utils/utils.hpp"
#include "../Entity/Entity.hpp"


class Game;

class World {
protected:
    // ENTITIES
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities{};
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
    T* createEntity(Args&&... args) {
        // Create entity
        auto pEntity = std::make_unique<T>(*this, std::forward<Args>(args)...);
        // Init entity
        pEntity->init();
        // Get its name
        const std::string entityName = pEntity->name;
        // Store in the list of entities
        entities.emplace(entityName, std::move(pEntity));
        return getEntity<T>(entityName);
    }

    // Create Entity at a defined position
    template<typename T, typename ... Args>
    T* createEntity(sf::Vector2f position, Args&&... args) {
        // Create the entity
        auto pEntity = std::make_unique<T>(*this, std::forward<Args>(args)...);
        // Init the entity
        pEntity->init();
        pEntity->shape.setPosition(position);
        // Get its name
        const std::string entityName = pEntity->name;
        // Store it in the list of entities
        entities.emplace(entityName, std::move(pEntity));
        return getEntity<T>(entityName);
    }

    template<typename T>
    T* getEntity(std::string entityName) {
        const auto NAME = text::up(std::move(entityName));
        const auto it = entities.find(NAME);
        if (it == entities.end()) return nullptr;
        return dynamic_cast<T*>(it->second.get());
    }

    std::unordered_map<std::string, std::unique_ptr<Entity>>* getEntities() {
        return &entities;
    }

    template<typename T>
    std::vector<T *> findEntities() const {
        std::vector<T*> entitiesOfType{};
        for (auto &entity: entities | std::views::values) {
            if (auto it = dynamic_cast<T*>(entity.get())) {
                entitiesOfType.emplace(entitiesOfType.end(), it);
            }
        }
        return entitiesOfType;
    }

    void remove(std::string entityName) {
        const auto NAME = text::up(std::move(entityName));
        const auto it = entities.find(NAME);
        entities.erase(it);
    }

    void update();
};
#endif //BONK_GAME_WORLD_HPP