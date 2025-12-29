//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_ENTITY_HPP
#define BONK_GAME_ENTITY_HPP

#include <string>
#include <SFML/Graphics/Shape.hpp>

using entityID = std::uint64_t;

class World;
class Game;


class Entity {
    const entityID ID;
public:
    virtual ~Entity();

    Entity(World &world, entityID ID);

    Entity(World &world, entityID ID, std::string name);
    // REFERENCES
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

    [[nodiscard]] entityID getID() const {return ID;}

    virtual sf::Shape* getShape() = 0;

    [[nodiscard]] virtual sf::Vector2f getWindowToShapeSizeRatio() const;

    virtual sf::Texture* getTexture() {return pTexture;}

    virtual void init();

    virtual void update() = 0;

    bool operator==(const Entity &other) const;

    bool operator!=(const Entity &other) const;
};


#endif //BONK_GAME_ENTITY_HPP