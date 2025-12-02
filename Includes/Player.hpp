//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP


#include <functional>
#include <SFML/Graphics.hpp>

#include "AnimationComponent.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"
#include "Entity.hpp"


class World;

class Player final : public Entity {
public:
    enum PlayerStates {
        IDLE,
        WINKING,
        WALKING,
        RUNNING,
        CROUCHING,
        JUMPING,
        DISAPPEARING,
        DYING,
        ATTACKING,
        BRAKING,
        STOPPING,
    };
#pragma region constructors
    explicit Player(const char* name);
    explicit Player(const char* name, const Controls &controls, sf::Texture &texture);
#pragma endregion
    // CHARACTERISTICS
    float health {100.f};
    float attackDamage{20.f};
    float height{250};
    float width{height};
    sf::Vector2f size{height, width};
    sf::Vector2f maxWalkingSpeed{size.x*2, size.x*1.5f};
    sf::Vector2f maxRunningSpeed{maxWalkingSpeed.x*2.f, maxWalkingSpeed.y*1.25f};
    sf::Vector2f maxSpeed{maxWalkingSpeed};
    float movementResponse{20.f};  // How aggressively player changes speed
    // PHYSICS
    sf::Vector2f position{0, 0};
    sf::Vector2f velocity{0, 0};
    sf::Vector2f acceleration{0, physics.GRAVITY};
    // STATES
    PlayerStates state{IDLE};
    // CONDITIONS
    bool facingRight{true};
    float eyeDryness{0};
    // COMPONENTS
    InputComponent input{};
    AnimationComponent animation{};
    PhysicsComponent physics{};
    // RENDERING
    sf::RectangleShape shape = sf::RectangleShape(size);
    // UTILITY
    void setPosition(const sf::Vector2f &newPosition);
    void moveShape(sf::Vector2f distance);
    // MOVEMENT
    void turn();
    std::function<void()> walk;
    void walkLeft();
    void walkRight();
    void brake();
    void jump();
    // COMBAT
    float attackRange{size.x/2.f};
    void attack();
    void takeDamage(const float &damage);
    void die();
    // UPDATE
    void declareState();
    void takeAction();
    void selectAnimation();
    void update() override;
};

#endif //BONK_GAME_PLAYER_HPP