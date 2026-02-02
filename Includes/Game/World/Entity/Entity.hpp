//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_ENTITY_HPP
#define BONK_GAME_ENTITY_HPP

#include <string>
#include <SFML/Graphics/Shape.hpp>

#include "Game/Engines/SceneGraph/Render.hpp"
#include "Game/Engines/SceneGraph/Composite.hpp"


using entityID = std::uint64_t;

class World;
class Game;


namespace entity {
    class Entity {
        const entityID id_;
        std::string name_{};
    public:
        #pragma region constructors
        virtual ~Entity();
        Entity(World &world, entityID ID, std::string name);
        #pragma endregion

        #pragma region operators
        bool operator==(const Entity &other) const;

        bool operator!=(const Entity &other) const;
        #pragma endregion

        // REFERENCES
        World &world;
        Game  &game;
        // CHARACTERISTICS
        sf::Vector2f position{};
        sf::Vector2f velocity{};
        sf::Vector2f acceleration{};
        // RENDER
        Render render;
        // FLAGS
        bool removalFlag = false;

        void rename(std::string entityName);

        std::string_view getName();

        [[nodiscard]] entityID getID() const;

        [[nodiscard]] static std::string getClassName();

        virtual void update() = 0;
    };
}

#endif //BONK_GAME_ENTITY_HPP