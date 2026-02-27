#include "Game/World/Entity/Actor/Components/MovementComponent.hpp"
#include "Game/Game.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"


actor::MovementComponent::MovementComponent(Actor &entity)
    : actor_(entity) {
}

void actor::MovementComponent::move(sf::Vector2f speed) const {
    const auto &input = actor_.bindings();

    const auto left = input.slotsHeld({{InputSlot::S2}});
    const auto right = input.slotsHeld({{InputSlot::S4}});
    const auto up = input.slotsHeld({{InputSlot::S1}});
    const auto down = input.slotsHeld({{InputSlot::S3}});

    const sf::Vector2i direction = {right - left, down - up};

    speed = hd::multiply(static_cast<sf::Vector2f>(direction), speed);

    turn(); // For convenience. Can be separated if needed movement without turning later.

    actor_.physics().accelerate(speed);
}

float actor::MovementComponent::getSpeedRatio(const sf::Vector2f expectedSpeed) const {
    return magnitudeRatio(expectedSpeed, actor_.physics().properties().velocity);
}

void actor::MovementComponent::turn() const {
    const auto &input = actor_.bindings();
    auto &render = actor_.getRender();
    const auto scale = render.getScale();

    const auto left = input.slotsHeld({{InputSlot::S2}});
    const auto right = input.slotsHeld({{InputSlot::S4}});
    const auto up = input.slotsHeld({{InputSlot::S1}});
    const auto down = input.slotsHeld({{InputSlot::S3}});

    if (const sf::Vector2i direction = {right - left, up - down};
        direction.x || direction.y) {
        render.setScale({
                static_cast<float>(std::copysign(scale.x, direction.x)),
                // static_cast<float>(std::copysign(scale.y, direction.y)) // If allowing flip along the horizontal axis
                scale.y
            }
        );
    }
}
