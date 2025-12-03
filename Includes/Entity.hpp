//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_ENTITY_HPP
#define BONK_GAME_ENTITY_HPP

#include <string>
#include <SFML/Graphics/Shape.hpp>


class World;

class Entity {
public:
    virtual ~Entity();

    explicit Entity(std::string name);

    std::string name{};
    sf::Shape *pShape{nullptr};
    sf::Texture *pTexture{nullptr};
    std::vector<sf::Shape*> pShapes{};
    std::vector<sf::Texture*> pTextures{};
    World *pWorld{nullptr};
    bool markedForRemoval = false;

    virtual void init(sf::Shape &shape, sf::Texture &texture);

    virtual void update();

    bool operator==(const Entity &other) const;

    bool operator!=(const Entity &other) const;
};


#endif //BONK_GAME_ENTITY_HPP