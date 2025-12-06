//
// Created by Andrew on 13/11/2025.
//

#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Utils/utils.hpp"
#include <iostream>

#include "../../../Includes/World/World.hpp"


#pragma region constructors
Player::Player(std::string name) : Entity(std::move(name)){}

Player::Player(std::string name, const Controls &controls) :
Entity(std::move(name)), input(*this, controls), physics(*this), animation(*this), actions(*this) {
    this->animation.animationSheet = {pTexture, {32, 32}};
    this->animation.target = &shape;
    animation.add(AnimationEntry(IDLE,         2, true));
    animation.add(AnimationEntry(WINKING,      2, true));
    animation.add(AnimationEntry(WALKING,      4, true));
    animation.add(AnimationEntry(RUNNING,      8, true));
    animation.add(AnimationEntry(CROUCHING,    6, true));
    animation.add(AnimationEntry(JUMPING,      8, false));
    animation.add(AnimationEntry(DYING,        8, false));
    animation.add(AnimationEntry(DISAPPEARING, 4, false));
    animation.add(AnimationEntry(ATTACKING,    8, false));
}
#pragma endregion

sf::Vector2f Player::getSize() const {
    return shape.getGlobalBounds().size;
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

void Player::setPosition(const sf::Vector2f &position) {
    shape.setPosition(position);
    physics.position = getPosition();
}

void Player::declareState() {
    const int desiredState = input.update();
    if (health <= 0) {
        state = DYING;
        return;
    }
    if (state == JUMPING) {
        if (physics.position.y  + getSize().y / 2.f >= pWorld->groundLevel) {
            state = IDLE;
        }
    }
    else if (state == ATTACKING) {
        if (animation.completed(ATTACKING)) {
            this->state=IDLE;
        }
    }
    else {  // ACTIONS NEED TO BE SORTED BY PRIORITY
        if (desiredState == JUMPING) {
            state = JUMPING;
        }
        else if (desiredState == ATTACKING) {
            state = ATTACKING;
        }
        else if (desiredState == WALKING) {
            state = WALKING;
        }
        else if (desiredState == RUNNING) {
            state = RUNNING;
        }
        else if (desiredState == STOPPING) {
            state = STOPPING;
        }
        else if (desiredState == IDLE) {
            if (std::fabs(physics.velocity.x) > 0) {
                state = BRAKING;
            }
            else state = IDLE;
        }
    }
}

void Player::takeAction() {
    switch (state) {
        case IDLE: {
            break;
        }
        case WINKING: {
            break;
        }
        case WALKING: {
            physics.speed = physics.walkingSpeed;
            actions.movement.walk();
            break;
        }
        case RUNNING: {
            physics.speed = physics.runningSpeed;
            actions.movement.walk();
            break;
        }
        case CROUCHING: {
            break;
        }
        case JUMPING: {
            actions.movement.jump();
            break;
        }
        case DISAPPEARING: {
            break;
        }
        case DYING: {
            actions.combat.die();
            break;
        }
        case ATTACKING: {
            actions.combat.attack();
            break;
        }
        case BRAKING: {
            actions.movement.brake();
            break;
        }
        case STOPPING: {
            actions.movement.brake();
            break;
        }
        default: {
        }
    }
}

void Player::initShapeSize() {
    shape.setSize(static_cast<sf::Vector2f>(pTexture->getSize()));
}

sf::Shape *Player::getShape() {
    return &shape;
}

sf::Texture *Player::getTexture() {
    return &pWorld->pGame->textures.player;
}

void Player::init() {
    Entity::init();
    const sf::Vector2f sizeRatio = getWindowToShapeSizeRatio() * height;
    pShape->setScale(sizeRatio);
}

void Player::update() {
    physics.acceleration = {0.f, pWorld->gravity};  // Reset acceleration
    declareState();
    animation.selectAnimation();
    takeAction();
    physics.update();
    animation.update(pWorld->pGame->time.dt);
}
