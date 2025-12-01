//
// Created by Andrew on 13/11/2025.
//

#include "../Includes/Player.hpp"
#include "../Includes/utils.hpp"
#include <iostream>

#include "../Includes/World.hpp"


#pragma region constructors
Player::Player() = default;

Player::Player(sf::Texture &texture, const Controls &controls) : input(controls) {
    Entity::init(shape, texture);
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

void Player::setPosition(const sf::Vector2f &newPosition) {
    shape.setPosition(newPosition);
    position = shape.getPosition();
}

void Player::moveShape(const sf::Vector2f distance) {
    shape.move(distance);
    position = shape.getPosition();
}

void Player::turn() {
    brake();
    if (areClose(velocity.x, 0.f, 10.f)) {
        if (facingRight) {
            shape.setScale({-1,1});
        }
        else {
            shape.setScale({1, 1});
        }
        facingRight = !facingRight;
    }
}

void Player::walkLeft() {
    if (facingRight) {
        turn();
    }
    else {
        physics.updateAcceleration(*this, -maxSpeed, movementResponse);
    }
}

void Player::walkRight() {
    if (!facingRight) {
        turn();
    }
    else {
        physics.updateAcceleration(*this, maxSpeed, movementResponse);
    }
}

void Player::brake() {
    physics.updateAcceleration(*this, {0.f, velocity.y}, movementResponse);
}

void Player::jump() {
    if (position.y + size.y / 2.f >= pWorld->groundLevel) {
        velocity.y = -physics.GRAVITY*maxSpeed.y/2500.f;  // Magic number is tweaked experimentally
    }
}

void Player::attack() {
    auto pPlayers = pWorld->findTypes<Player>();
    std::erase(pPlayers, this);
    for (Player *player : pPlayers) {
        if (std::fabs(player->position.x - position.x) <= attackRange) {
            animation.onEnd(ATTACKING, [&player, this]{player->takeDamage(this->attackDamage);});
        }
    }
}

void Player::takeDamage(const float &damage) {
    health -= damage;
}

void Player::die() {
    animation.onEnd(DYING, [this]{this->markedForRemoval=true;});
}

void Player::declareState() {
    const int desiredState = input.update(*this);
    if (health <= 0) {
        state = DYING;
        return;
    }
    if (state == JUMPING) {
        if (position.y  + size.y / 2.f >= pWorld->groundLevel) {
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
            if (std::fabs(velocity.x) > 0) {
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
            maxSpeed = maxWalkingSpeed;
            walk();
            break;
        }
        case RUNNING: {
            maxSpeed = maxRunningSpeed;
            walk();
            break;
        }
        case CROUCHING: {
            break;
        }
        case JUMPING: {
            jump();
            break;
        }
        case DISAPPEARING: {
            break;
        }
        case DYING: {
            die();
            break;
        }
        case ATTACKING: {
            attack();
            break;
        }
        case BRAKING: {
            brake();
            break;
        }
        case STOPPING: {
            brake();
            break;
        }
        default: {
        }
    }
}

void Player::selectAnimation() {
    switch (state) {
        case JUMPING : {
            animation.set(JUMPING);
            animation.animationSet[JUMPING].fps = std::fabs(maxWalkingSpeed.y / maxSpeed.y)*24.f;
            break;
        }
        case WALKING : {
            animation.set(WALKING);
            animation.pCurrentAnimation->fps = std::fabs(velocity.x / maxWalkingSpeed.x) * static_cast<float>(animation.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case RUNNING : {
            animation.set(RUNNING);
            animation.pCurrentAnimation->fps = std::fabs(velocity.x / maxRunningSpeed.x) * static_cast<float>(animation.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case ATTACKING : {
            animation.set(ATTACKING);
            animation.pCurrentAnimation->fps = static_cast<float>(animation.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        case DYING : {
            animation.set(DYING);
            // animation.pCurrentAnimation->fps = static_cast<float>(animation.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        default: {
            animation.set(IDLE);
        }
    }
}

void Player::update() {
    acceleration = {0.f, physics.GRAVITY};  // Reset acceleration

    declareState();
    selectAnimation();
    takeAction();

    physics.update(*this, pWorld->pGame->dt);
    animation.update(pWorld->pGame->dt);
}