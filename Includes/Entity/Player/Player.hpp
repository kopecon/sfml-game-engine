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
#include "../../Game/Engines/StateMachine/StateMachine.hpp"


class World;

namespace player {
    class Player final : public Entity {
    public:
#pragma region constructors
        explicit Player(World &world, std::string name);
        explicit Player(World &world, std::string name, const Controls &controls);
#pragma endregion
        // CHARACTERISTICS
        float health {100.f};
        float attackDamage{20.f};
        float height{0.2f};  // As a factor of the window height. (from 0 to 1)
        // CONDITIONS
        bool facingRight{true};
        float eyeDryness{};
        // COMPONENTS
        InputComponent input{};
        PhysicsComponent physics;
        MovementComponent movement;
        CombatComponent combat{};
        // MANAGERS
        AnimationManager animationManager{};
        StateMachine<StateSet> stateMachine{};
        // RENDERING
        sf::RectangleShape shape{};
        // GETTERS
        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;
        StateSet::ID getStateID() const;
        // OVERRIDES
        void initShapeSize() override;
        sf::Shape* getShape() override;
        sf::Texture* getTexture() override;
        void init() override;
        // UPDATE
        void update() override;
    };
}


#endif //BONK_GAME_PLAYER_HPP