//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_ENTITY_HPP
#define BONK_GAME_ENTITY_HPP

#include <SFML/Graphics/Shape.hpp>

class World;

class Entity {
public:
    virtual ~Entity();

    sf::Shape *pShape{nullptr};
    std::vector<sf::Shape*> pShapes{nullptr};
    World *pWorld{nullptr};
    bool markedForRemoval = false;

    virtual void update(const float &dt);

    bool operator==(const Entity &other) const;

    bool operator!=(const Entity &other) const;
};


#endif //BONK_GAME_ENTITY_HPP