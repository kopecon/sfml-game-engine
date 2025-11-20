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
            acceleration.x = -speed.x*physics.GROUND_FRICTION;
        }
    }

    void Player::walkRight() {
        if (!facingRight) {
            turn();
        }
        else {
            acceleration.x = speed.x*physics.GROUND_FRICTION;
        }
    }

    void Player::turn() {
        brake(2.f);
        if (std::fabs(velocity.x) <= 100.f){
            if (facingRight) {
                shape.setScale({-1,1});
            }
            else
            {
                shape.setScale({1, 1});
            }
            facingRight = !facingRight;
        }
    }

    void Player::brake() {
        if (std::fabs(velocity.x) >= 1) {
            acceleration.x = -std::copysign(speed.x, velocity.x)*physics.GROUND_FRICTION;
        }
    }

    void Player::brake(const float &breakFactor) {
        if (std::fabs(velocity.x) >= 1) {
            acceleration.x = -std::copysign(speed.x, velocity.x)*physics.GROUND_FRICTION*breakFactor;
        }
    }

    void Player::jump() {
        if (position.y == physics.GROUND_LEVEL) {
            velocity.y = -physics.GRAVITY/5.f*speed.y/500.f;
            animation.animationSet[JUMP].fps = std::fabs(walkingSpeed.y/speed.y*24.f);
        }
    }

    void Player::update(const float &dt) {
        acceleration = {0.f, physics.GRAVITY};  // Reset acceleration

        input.update(*this);

        if (state != isJUMPING) {
            if (std::fabs(velocity.x + 1) <= walkingSpeed.x) {
                state = isWALKING;
            }
            else if (std::fabs(velocity.x + 1) > walkingSpeed.x) {
                state = isRUNNING;
            }
            else if (std::fabs(velocity.x) <= speed.x/2.f) {
                brake();
                state = isIDLE;
            }
        }

        physics.update(*this, dt);
        animation.update(*this, dt);
    }
} // entities
