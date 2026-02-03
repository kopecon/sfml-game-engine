#include "Game/World/Entity/Player/Player.hpp"
#include "Game/World/World.hpp"


namespace player {
    using enum StateSet::ID;

    #pragma region constructors
    Player::Player(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name))
        {}

    Player::Player(World &world, const entityID ID, std::string name, const Controls &controls) :
        Entity(world, ID, std::move(name)),
        input_(*this, controls)
        {}

    void Player::setEyeDryness(const float value) {
        eyeDryness_ = value;
    }

#pragma endregion

    std::string Player::getClassName() {
        return "Player";
    }

    sf::Vector2f Player::getCharacterSize() const {
        return {height_, width_};
    }

    const State<StateSet>& Player::getCurrentState() const {
        return stateManager_.getEngine().getCurrentState();
    }

    const State<StateSet>& Player::getPreviousState() const {
        return stateManager_.getEngine().getPreviousState();
    }

    float Player::getEyeDryness() const {
        return eyeDryness_;
    }

    InputComponent & Player::getInput() {
        return input_;
    }

    PhysicsComponent & Player::getPhysics() {
        return physics_;
    }

    MovementComponent & Player::getMovement() {
        return movement_;
    }

    void Player::update() {
        // physics_.setVerbose(true);
        physics_.update();
        stateManager_.update();
    }
}
