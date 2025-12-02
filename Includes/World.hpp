//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_WORLD_HPP
#define BONK_GAME_WORLD_HPP
#include <iostream>
#include <ranges>
#include <vector>
#include "Entity.hpp"
#include "Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class Game;
class Entity;

class World {
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities{};
public:
    World();
    explicit World(const char* name);

    const char *name{};
    Game *pGame{nullptr};
    float groundLevel{0};

    template<typename T, typename... Args>
    void createEntity(Args&&... args) {
        auto pEntity = std::make_unique<T>(std::forward<Args>(args)...);
        pEntity->pWorld = this;
        entities.emplace(pEntity->name, std::move(pEntity));
    }

    void add(Entity &entity);

    template<typename T>
    std::vector<T*> findEntities();

    void remove(const Entity *entity);

    void draw() const;

    void update();
};

template<typename T>
std::vector<T *> World::findEntities() {
    std::vector<T*> entitiesOfType{};
    for (auto &entity: entities | std::views::values) {
        if (auto it = dynamic_cast<T*>(entity.get())) {
            entitiesOfType.emplace(entitiesOfType.end(), it);
        }
    }
    return entitiesOfType;
}

#endif //BONK_GAME_WORLD_HPP
