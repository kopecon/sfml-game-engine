//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_WORLD_HPP
#define BONK_GAME_WORLD_HPP
#include <ranges>
#include <iostream>
#include <vector>
#include "../Entity/Entity.hpp"
#include "../Game/Game.hpp"
#include "../../Utils/utils.hpp"


class Game;
class Entity;

class World {
    // ENTITIES
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities{};
public:
    World();
    explicit World(std::string name);
    // METADATA
    std::string name{};
    // GAME POINTER
    Game *pGame{nullptr};
    // ENVIRONMENT CHARACTERISTIC
    const float gravity = 10000;
    const float airFriction = 0.f;
    const float groundFriction = 1.f;
    float groundLevel{};

    // Create Entity at [0, 0]
    template<typename T, typename ... Args>
    T* createEntity(Args&&... args) {
        auto pEntity = std::make_unique<T>(std::forward<Args>(args)...);
        pEntity->pWorld = this;
        pEntity->init();
        const std::string entityName = pEntity->name;
        entities.emplace(entityName, std::move(pEntity));
        return getEntity<T>(entityName);
    }

    // Create Entity at a defined position
    template<typename T, typename ... Args>
    T* createEntity(sf::Vector2f position, Args&&... args) {
        auto pEntity = std::make_unique<T>(std::forward<Args>(args)...);
        pEntity->pWorld = this;
        pEntity->init();
        pEntity->shape.setPosition(position);
        const std::string entityName = pEntity->name;
        entities.emplace(entityName, std::move(pEntity));
        return getEntity<T>(entityName);
    }

    template<typename T>
    T* getEntity(std::string entityName) {
        text::up(entityName);
        const auto it = entities.find(entityName);
        if (it == entities.end()) return nullptr;
        return dynamic_cast<T*>(it->second.get());
    }

    template<typename T>
    std::vector<T *> findEntities() {
        std::vector<T*> entitiesOfType{};
        for (auto &entity: entities | std::views::values) {
            if (auto it = dynamic_cast<T*>(entity.get())) {
                entitiesOfType.emplace(entitiesOfType.end(), it);
            }
        }
        return entitiesOfType;
    }

    void remove(std::string entityName) {
        text::up(entityName);
        const auto it = entities.find(entityName);
        entities.erase(it);
    }

    void draw() const;

    void update();
};
#endif //BONK_GAME_WORLD_HPP