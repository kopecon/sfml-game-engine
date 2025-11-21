//
// Created by Andrew on 13/11/2025.
//

#include "../Includes/Player.hpp"

namespace entities {
    Player::Player() = default;

    Player::Player(sf::Texture &texture, const Controls &controls) : input(controls) {
        this->pTexture = &texture;
        this->animation.animationSheet = {pTexture, {32, 32}};
        this->pTexture->setRepeated(false);
        this->shape.setTexture(&texture);
        this->shape.setOrigin(shape.getGeometricCenter());
        animation.add(AnimationEntry(IDLE,      2, true));
        animation.add(AnimationEntry(WINK,      2, true));
        animation.add(AnimationEntry(WALK,      4, true));
        animation.add(AnimationEntry(RUN,       8, true));
        animation.add(AnimationEntry(CROUCH,    6, true));
        animation.add(AnimationEntry(JUMP,      8, false));
        animation.add(AnimationEntry(DIE,       8, false));
        animation.add(AnimationEntry(DISAPPEAR, 4, false));
        animation.add(AnimationEntry(ATTACK,    8, false));
        this->shape.setTextureRect(animation.getFrame());
    }

    void Player::setPosition(const sf::Vector2f &newPosition) {
        shape.setPosition(newPosition);
        position = shape.getPosition();
    }

    void Player::move(const sf::Vector2f distance) {
        shape.move(distance);
        position = shape.getPosition();
    }

    void Player::walkLeft() {
        if (facingRight) {
            turn();
        }
        else {
            physics.calculateAcceleration(*this, -maxSpeed, 20.f);
        }
    }

    void Player::walkRight() {
        if (!facingRight) {
            turn();
        }
        else {
            physics.calculateAcceleration(*this, maxSpeed, 20.f);
        }
    }

    void Player::turn() {
        physics.brake(*this, 2.f);
        if (std::fabs(velocity.x) <= 100.f){
            if (facingRight) {
                shape.setScale({-1,1});
            }
            else {
                shape.setScale({1, 1});
            }
            facingRight = !facingRight;
        }
    }

    void Player::jump() {
        if (position.y == physics.GROUND_LEVEL) {
            velocity.y = -physics.GRAVITY*maxSpeed.y/2500.f;
            animation.animationSet[JUMP].fps = std::fabs(maxWalkingSpeed.y/maxSpeed.y*24.f);
        }
    }

    void Player::update(const float &dt) {
        acceleration = {0.f, physics.GRAVITY};  // Reset acceleration

        if (state != JUMPING) {
            if (std::fabs(velocity.x) > 0.f && std::fabs(velocity.x) - 1 <= maxWalkingSpeed.x) {
                state = WALKING;
            }
            else if (std::fabs(velocity.x) - 1 > maxWalkingSpeed.x) {
                state = RUNNING;
            }

            else {
                state = isIDLE;
            }
        }

        input.update(*this);
        physics.update(*this, dt);
        animation.update(*this, dt);
    }
} // entities
