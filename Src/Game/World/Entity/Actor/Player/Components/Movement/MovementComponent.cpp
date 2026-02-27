#include "Game/World/Entity/Actor/Player/Components/Movement/MovementComponent.hpp"
#include "Game/Game.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"
#include "Game/World/Entity/Actor/Player/Components/Render/PlayerSprite.hpp"


player::MovementComponent::MovementComponent(Player &player)
    : player_(player), speed_(getWalkingSpeed()) {
}

void player::MovementComponent::move(sf::Vector2f speed) const {
    const auto &input = player_.bindings();

    const auto left = input.slotsHeld({{InputSlot::S2}});
    const auto right = input.slotsHeld({{InputSlot::S4}});
    const auto up = input.slotsHeld({{InputSlot::S1}});
    const auto down = input.slotsHeld({{InputSlot::S3}});

    const sf::Vector2i direction = {right - left, down - up};
    speed = hd::multiply(static_cast<sf::Vector2f>(direction), speed);

    turn(); // For convenience. Can be separated if needed movement without turning later.

    player_.physics().accelerate(speed, getSnap(), getSpeed());
}

void player::MovementComponent::setSpeed(const sf::Vector2f speed) {
    speed_ = speed;
}

void player::MovementComponent::setWalkingSpeed(const sf::Vector2f speed) {
    walkingSpeedMultiplier_ = speed;
    assert(getWalkingSpeed().x > getRunningSpeed().x);
    assert(getWalkingSpeed().y > getRunningSpeed().y);
}

void player::MovementComponent::setRunningSpeed(const sf::Vector2f speed) {
    runningSpeedMultiplier_ = speed;
    assert(getWalkingSpeed().x > getRunningSpeed().x);
    assert(getWalkingSpeed().y > getRunningSpeed().y);
}

void player::MovementComponent::setSnap(const sf::Vector2f snap) {
    snap_ = snap;
}

sf::Vector2f player::MovementComponent::getSpeed() const {
    return speed_;
}

sf::Vector2f player::MovementComponent::getWalkingSpeed() const {
    return hd::multiply(player_.getCharacterSize(), walkingSpeedMultiplier_);;
}

sf::Vector2f player::MovementComponent::getRunningSpeed() const {
    return hd::multiply(player_.getCharacterSize(), runningSpeedMultiplier_);
}

sf::Vector2f player::MovementComponent::getSnap() const {
    return snap_;
}

float player::MovementComponent::getSpeedRatio() const {
    return magnitudeRatio(speed_, player_.physics().properties().velocity);
}

void player::MovementComponent::turn() const {
    const auto &input = player_.bindings();
    auto &playerSprite = player_.getRenderManager().getMainSprite();
    const auto scale = playerSprite.getScale();

    const auto left = input.slotsHeld({{InputSlot::S2}});
    const auto right = input.slotsHeld({{InputSlot::S4}});
    const auto up = input.slotsHeld({{InputSlot::S1}});
    const auto down = input.slotsHeld({{InputSlot::S3}});

    if (const sf::Vector2i direction = {right - left, up - down};
        direction.x || direction.y) {
        playerSprite.setScale({
                static_cast<float>(std::copysign(scale.x, direction.x)),
                // static_cast<float>(std::copysign(scale.y, direction.y)) // If allowing flip along the horizontal axis
            scale.y
            }
        );
    }
}
