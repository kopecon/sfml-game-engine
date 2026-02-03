//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Game/Engines/StateMachine/State.hpp"
#include "Game/World/Entity/Entity.hpp"
#include "Game/World/Entity/Player/Components/States/StateSet.hpp"
#include "Game/World/Entity/Player/Components/PhysicsComponent.hpp"
#include "Game/World/Entity/Player/Components/Input/InputComponent.hpp"
#include "Game/World/Entity/Player/Components/Movement/MovementComponent.hpp"
#include "Game/World/Entity/Player/Components/Combat/CombatComponent.hpp"
#include "Game/World/Entity/Player/Components/Render/RenderManager.hpp"
#include "Game/World/Entity/Player/Components/States/StateManager.hpp"


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
        void setEyeDryness(float value);
        // GETTERS
        [[nodiscard]] static std::string getClassName();
        [[nodiscard]] sf::Vector2f getCharacterSize() const;
        [[nodiscard]] const State<StateSet>& getCurrentState() const;
        [[nodiscard]] const State<StateSet>& getPreviousState() const;
        [[nodiscard]] float getEyeDryness() const;
        [[nodiscard]] InputComponent& getInput();
        [[nodiscard]] PhysicsComponent& getPhysics();
        [[nodiscard]] MovementComponent& getMovement();

    private:
        // CHARACTERISTICS
        float height_{256.f/1.5};
        float width_{256.f/1.5};
        // CONDITIONS
        float eyeDryness_{};
        // MANAGERS
        StateManager stateManager_{*this};
        RenderManager renderManager_{*this};
        // COMPONENTS
        InputComponent input_{*this};
        PhysicsComponent physics_{*this};
        MovementComponent movement_{*this};
        CombatComponent combat_{*this};
        // UPDATE
        void update() override;
    };
} //player


#endif //BONK_GAME_PLAYER_HPP