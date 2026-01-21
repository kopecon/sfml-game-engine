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
        explicit Player(World &world, entityID ID, std::string name);
        explicit Player(World &world, entityID ID, std::string name, const Controls &controls);
#pragma endregion

        // CHARACTERISTICS
        float health{100.f};
        float attackDamage{20.f};
        float height{256.f/1.5};
        float width{256.f/1.5};
        // CONDITIONS
        bool facingRight{true};
        float eyeDryness{};
        // COMPONENTS
        InputComponent input{*this};
        PhysicsComponent physics{*this};
        MovementComponent movement{*this};
        CombatComponent combat{*this};
        // MANAGERS
        StateManager stateManager{*this};
        RenderManager renderManager{*this};
        AnimationManager animationManager{*this};
        // GETTERS
        [[nodiscard]] static std::string getClassName();
        [[nodiscard]] sf::Vector2f getCharacterSize() const;
        [[nodiscard]] const State<StateSet>& getState() const;
        [[nodiscard]] sf::Sprite& getSprite();

        // UPDATE
        void update() override;
    };
}


#endif //BONK_GAME_PLAYER_HPP