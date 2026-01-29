//
// Created by Andrew on 20/11/2025.
//

#include "../../../Includes/Entity/Player/InputComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/StateSet.hpp"
#include "../../../Includes/Game/Game.hpp"


#pragma region constructors
player::InputComponent::InputComponent(Player &player) : player_(player) {
}

player::InputComponent::InputComponent(Player &player, const Controls &controls):
    player_(player),
    controls_(controls) {
    player_.game.getEventHandler().subscribe(eventSubscriber);
}

player::InputComponent::~InputComponent() {
    player_.game.getEventHandler().unsubscribe(eventSubscriber);
}
#pragma endregion

    void player::InputComponent::update() const {
    const bool left        = sf::Keyboard::isKeyPressed(controls_.left       );
    const bool right       = sf::Keyboard::isKeyPressed(controls_.right      );
    const bool jump        = sf::Keyboard::isKeyPressed(controls_.jump       );
    const bool run         = sf::Keyboard::isKeyPressed(controls_.run        );
    const bool attack      = sf::Keyboard::isKeyPressed(controls_.attack     );
    const bool crouch      = sf::Keyboard::isKeyPressed(controls_.crouch     );
    const bool concentrate = sf::Keyboard::isKeyPressed(controls_.concentrate);

    using enum StateSet::ID;

    // ACTIONS NEED TO BE SORTED BY PRIORITY
    if (jump) player_.setDesiredState(JUMPING);
    else if (attack) player_.setDesiredState(ATTACKING);
    else if (left && right) player_.setDesiredState(STOPPING);
    else if (left) {
        player_.getMovement().setLeftWalkingDirection();
        if (run) player_.setDesiredState(RUNNING);
        else player_.setDesiredState(WALKING);
        }
    else if (right) {
        player_.getMovement().setRightWalkingDirection();
        if (run) player_.setDesiredState(RUNNING);
        else player_.setDesiredState(WALKING);
        }
    else if (concentrate) {
        player_.setDesiredState(CONCENTRATING);
    }
    else if (crouch) {
        player_.setDesiredState(CROUCHING);
    }
    else
    player_.setDesiredState(IDLE);
}

void player::InputComponent::handlePressedKey(const sf::Event::KeyPressed &keyPressed) {
    std::cout << StateSet::name(player_.getCurrentState().getID()) << "\n";
}
