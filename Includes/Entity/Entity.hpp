//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_ENTITY_HPP
#define BONK_GAME_ENTITY_HPP

#include <string>
#include <SFML/Graphics/Shape.hpp>


class World;
class Game;


class Entity {
public:
    virtual ~Entity();

    explicit Entity(World &world, std::string name);
    // REFERENCES  //TODO: Should references be const? Currently player can modify world or game
    World &world;
    Game  &game;
    // CHARACTERISTICS
    const std::string name{};
    sf::Vector2f *pSize{nullptr};
    // RENDER
    sf::Shape *pShape{nullptr};
    sf::Texture *pTexture{nullptr};
    // FLAGS
    bool removalFlag = false;

    virtual void initShapeSize() = 0;

    virtual sf::Shape* getShape() = 0;

    [[nodiscard]] virtual sf::Vector2f getWindowToShapeSizeRatio() const;

    virtual sf::Texture* getTexture() {return pTexture;}

    virtual void init();

    virtual void update() = 0;

    bool operator==(const Entity &other) const;

    bool operator!=(const Entity &other) const;
};


#endif //BONK_GAME_ENTITY_HPP