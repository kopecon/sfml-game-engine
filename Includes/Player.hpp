//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP


#include <functional>
#include <SFML/Graphics.hpp>
#include "../Includes/AnimationComponent.hpp"
#include "../Includes/PhysicsComponent.hpp"
#include "../Includes/InputComponent.hpp"


namespace entities {
    class Player {
    public:
        enum PlayerAnimations {
            IDLE,
            WINK,
            WALK,
            RUN,
            CROUCH,
            JUMP,
            DISAPPEAR,
            DIE,
            ATTACK
        };
        enum PlayerStates {
            isIDLE,
            isWINKING,
            isWALKING,
            isRUNNING,
            isCROUCHING,
            isJUMPING,
            isDISAPPEARING,
            isDYING,
            isATTACKING
        };
#pragma region constructors
        Player();
        explicit Player(sf::Texture &texture, const Controls &controls);
#pragma endregion
        // Components
        InputComponent input{};
        AnimationComponent animation{};
        PhysicsComponent physics{};

        // Physics
        sf::Vector2f position{0, 0};
        sf::Vector2f velocity{0, 0};
        sf::Vector2f acceleration{0, physics.GRAVITY};

        // Characteristics
        float health {100.f};
        float attackDamage{20.f};
        sf::Vector2f size = {250, 250};
        sf::Vector2f walkingSpeed{size.x*3.f, size.x*2.f};
        sf::Vector2f runningSpeed{walkingSpeed.x*2.f, walkingSpeed.y*1.25f};
        sf::Vector2f speed{walkingSpeed};

        // Rendering
        sf::Texture *pTexture{};
        sf::RectangleShape shape = sf::RectangleShape(size);

        // STATES
        PlayerStates state{isIDLE};
        bool falling{false};
        bool facingRight{true};
        float eyeDryness{0};

        std::function<void()> walk;
        void setPosition(const sf::Vector2f &newPosition);
        void move(sf::Vector2f distance);
        void update(const float &dt);
        void take_damage(const float &damage);
        void walkLeft();
        void walkRight();
        void brake();
        void brake(const float &breakFactor);
        void jump();
        void turn();
        void attack();
        void die();
        void manageAnimations();
        Controls controls{};
    };
} // entities

#endif //BONK_GAME_PLAYER_HPP