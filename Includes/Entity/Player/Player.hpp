//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_PLAYER_HPP
#define BONK_GAME_PLAYER_HPP


#include <functional>
#include <SFML/Graphics.hpp>

#include "../AnimationComponent.hpp"
#include "PhysicsComponent.hpp"
#include "InputComponent.hpp"
#include "../Entity.hpp"


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
    explicit Player(std::string name);
    explicit Player(std::string name, const Controls &controls);
#pragma endregion
    // CHARACTERISTICS
    float health {100.f};
    float attackDamage{20.f};
    float height{0.2f};  // As a factor of the window height. (from 0 to 1)
    sf::Vector2f maxWalkingSpeed{};
    sf::Vector2f maxRunningSpeed{};
    sf::Vector2f maxSpeed{};
    float movementResponse{0.05};  // How aggressively player changes speed
    // PHYSICS
    sf::Vector2f position{};
    sf::Vector2f velocity{};
    sf::Vector2f acceleration{};
    // STATES
    PlayerStates state{IDLE};
    // CONDITIONS
    bool facingRight{true};
    float eyeDryness{};
    // COMPONENTS
    InputComponent input{};
    AnimationComponent animation{};
    PhysicsComponent physics{};
    // RENDERING
    sf::RectangleShape shape{};
    // UTILITY
    void setPosition(const sf::Vector2f &newPosition);
    void moveShape(sf::Vector2f distance);
    // MOVEMENT
    void calculateSpeed();
    void turn();
    std::function<void()> walk;
    void walkLeft();
    void walkRight();
    void brake();
    void jump();
    // COMBAT
    float attackRange{};
    void attack();
    void takeDamage(const float &damage);
    void die();
    // UPDATE
    void declareState();
    void takeAction();
    void selectAnimation();
    void initShapeSize() override;
    sf::Shape* getShape() override;
    sf::Texture* getTexture() override;
    void init() override;
    void update() override;
};

#endif //BONK_GAME_PLAYER_HPP