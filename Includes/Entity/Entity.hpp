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


namespace entity {

    class Entity {
        const entityID ID;
        std::string name{};
    public:
        #pragma region constructors
        virtual ~Entity();
        Entity(World &world, entityID ID);

        Entity(World &world, entityID ID, std::string name);

        [[nodiscard]] virtual std::string className() const;
        #pragma endregion

        // REFERENCES
        World &world;
        Game  &game;
        // CHARACTERISTICS
        sf::Vector2f *pSize{nullptr};
        // RENDER
        sf::Shape *pShape{nullptr};
        sf::Texture *pTexture{nullptr};
        // FLAGS
        bool removalFlag = false;

        void setName(std::string entityName) {
            name = std::move(entityName);
        }

        std::string_view getName() {
            return name;
        }

        virtual void initShapeSize() = 0;

        [[nodiscard]] entityID getID() const {return ID;}

        [[nodiscard]] virtual sf::Shape* getShape() = 0;

        [[nodiscard]] virtual sf::Vector2f getWindowToShapeSizeRatio() const;

        virtual sf::Texture* getTexture() {return pTexture;}

        virtual void init();

        virtual void update() = 0;

        bool operator==(const Entity &other) const;

        bool operator!=(const Entity &other) const;

    protected:
        [[nodiscard]] std::string generateName() const;
    };
}

#endif //BONK_GAME_ENTITY_HPP