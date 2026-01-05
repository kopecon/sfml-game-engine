//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "../Entity.hpp"
#include "States/StateSet.hpp"
#include "AnimationManager.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"
#include "MovementComponent.hpp"
#include "CombatComponent.hpp"
#include "RenderManager.hpp"
#include "States/StateManager.hpp"


class World;

namespace player {
    class Player final : public entity::Entity {
    public:
#pragma region constructors
        explicit Player(World &world, entityID ID);
        explicit Player(World &world, entityID ID, const Controls &controls);
        explicit Player(World &world, entityID ID, std::string name);
        explicit Player(World &world, entityID ID, std::string name, const Controls &controls);
#pragma endregion

        // CHARACTERISTICS
        float health{100.f};
        float attackDamage{20.f};
        float height{256.f};
        float width{256.f};
        // CONDITIONS
        bool facingRight{true};
        float eyeDryness{};
        // COMPONENTS
        InputComponent input;
        PhysicsComponent physics;
        MovementComponent movement;
        CombatComponent combat;
        // MANAGERS
        RenderManager renderManager;
        AnimationManager animationManager;
        StateManager stateManager;
        // GETTERS
        [[nodiscard]] sf::Vector2f getSize() const;
        [[nodiscard]] const State<StateSet>& getState() const;
        [[nodiscard]] sf::Shape& getShape() const;
        // UPDATE
        void update() override;

        [[nodiscard]] std::string getClassName() const override;
    };
}


#endif //BONK_GAME_PLAYER_HPP