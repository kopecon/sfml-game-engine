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
Entity(std::move(name)), input(*this, controls), physics(*this), animation(*this) {
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

void Player::turn() {
    brake();
    if (areClose(physics.velocity.x, 0.f, 10.f)) {
        shape.setScale({-shape.getScale().x, shape.getScale().y});
        facingRight = !facingRight;
    }
}

void Player::walkLeft() {
    if (facingRight) turn();
    else physics.accelerate(-physics.speed);
}

void Player::walkRight() {
    if (!facingRight) turn();
    else physics.accelerate(physics.speed);
}

void Player::brake() {
    physics.accelerate({0.f, physics.velocity.y});
}

void Player::jump() {
    if (physics.position.y + getSize().y / 2.f >= pWorld->groundLevel) {
        physics.velocity.y = -pWorld->gravity*physics.speed.y/2500.f;  // Magic number is tweaked experimentally
    }
}

void Player::attack() {
    auto pPlayers = pWorld->findEntities<Player>();
    std::erase(pPlayers, this);
    for (Player *opponent : pPlayers) {
        if (hd::abs(opponent->physics.position - physics.position).x <= attackRange &&
            hd::abs(opponent->physics.position - physics.position).y <= attackRange) {
            animation.onEnd(ATTACKING, [&opponent, this]{opponent->takeDamage(this->attackDamage);});
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
            walk();
            break;
        }
        case RUNNING: {
            physics.speed = physics.runningSpeed;
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
            animation.animationSet[JUMPING].fps = std::fabs(physics.walkingSpeed.y / physics.speed.y)*24.f;
            break;
        }
        case WALKING : {
            animation.set(WALKING);
            animation.pCurrentAnimation->fps = std::fabs(physics.velocity.x / physics.walkingSpeed.x) * static_cast<float>(animation.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case RUNNING : {
            animation.set(RUNNING);
            animation.pCurrentAnimation->fps = std::fabs(physics.velocity.x / physics.runningSpeed.x) * static_cast<float>(animation.pCurrentAnimation->framesPerRow) * 2.f;
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
    selectAnimation();
    takeAction();
    physics.update();
    animation.update(pWorld->pGame->time.dt);
}
