#ifndef BONK_GAME_ENTITY_HPP
#define BONK_GAME_ENTITY_HPP

#include "Game/World/Entity/Components/PhysicsComponent.hpp"
#include "Game/Engines/SceneGraph/Render.hpp"


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
        const World &world;
        const Game &game;
        // FLAGS
        bool removalFlag = false;

        // SETTERS
        void rename(std::string entityName);

        // GETTERS
        [[nodiscard]] entityID getID() const;

        [[nodiscard]] PhysicsComponent &physics();

        [[nodiscard]] Render& getRender();

        [[nodiscard]] std::string_view getName();

        [[nodiscard]] static std::string getClassName();


        // UPDATES
        virtual void update() = 0;

    protected:
        // COMPONENTS
        PhysicsComponent physics_{*this};
        Render render_{*this};
    };
}

#endif //BONK_GAME_ENTITY_HPP
