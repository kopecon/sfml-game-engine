//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_WORLD_HPP
#define BONK_GAME_WORLD_HPP
#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class Game;
class Entity;

class World {
    std::vector<Entity*> entities{};
public:
    Game *pGame{nullptr};
    float groundLevel{0};

    void add(Entity &entity);

    template<typename T>
    std::vector<T*> findTypes();

    void remove(const Entity *entity);

    void draw() const;

    void update();
};

template<typename T>
std::vector<T *> World::findTypes() {
    std::vector<T*> listOfTypes{};
    for (auto *entity : entities) {
        if (auto it = dynamic_cast<T*>(entity)) {
            listOfTypes.emplace(listOfTypes.end(), it);
        }
    }
    return listOfTypes;
}

#endif //BONK_GAME_WORLD_HPP
