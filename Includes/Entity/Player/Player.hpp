//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "../Entity.hpp"
#include "States/StateSet.hpp"
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
        // ACTIONS
        // SETTERS
        void setDesiredState(typename StateSet::ID id);
        void setFacingRight(bool value);
        void setEyeDryness(float value);
        // GETTERS
        [[nodiscard]] static std::string getClassName();
        [[nodiscard]] sf::Vector2f getCharacterSize() const;
        [[nodiscard]] const State<StateSet>& getCurrentState() const;
        [[nodiscard]] const State<StateSet>& getPreviousState() const;
        [[nodiscard]] bool isFacingRight() const;
        [[nodiscard]] float getEyeDryness() const;
        [[nodiscard]] PhysicsComponent& getPhysics();
        [[nodiscard]] MovementComponent& getMovement();

    private:
        // CHARACTERISTICS
        float height_{256.f/1.5};
        float width_{256.f/1.5};
        // CONDITIONS
        bool facingRight_{true};
        float eyeDryness_{};
        // COMPONENTS
        InputComponent input_{*this};
        PhysicsComponent physics_{*this};
        MovementComponent movement_{*this};
        CombatComponent combat_{*this};
        // MANAGERS
        StateManager stateManager_{*this};
        RenderManager renderManager_{*this};
        // UPDATE
        void update() override;
    };
} //player


#endif //BONK_GAME_PLAYER_HPP