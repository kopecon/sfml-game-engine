#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"


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

    void Player::walk() const {
        movement_.walk();
    }

    void Player::brake() const {
        movement_.brake();
    }

    void Player::jump() const {
        movement_.jump();
    }

    void Player::setDesiredState(const StateSet::ID state) {
        stateManager_.stateMachine.desiredStateID = state;
    }

    void Player::setLeftWalkingDirection() {
        movement_.walk = [&]{movement_.walkLeft();};
    }

    void Player::setRightWalkingDirection() {
        movement_.walk = [&]{movement_.walkRight();};
    }

    void Player::setFacingRight(const bool value) {
        facingRight_ = value;
    }

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
        assert(stateManager_.stateMachine.pCurrentState);
        return *stateManager_.stateMachine.pCurrentState;
    }

    const State<StateSet>& Player::getPreviousState() const {
        assert(stateManager_.stateMachine.pPreviousState);
        return *stateManager_.stateMachine.pPreviousState;
    }

    sf::Vector2f Player::getMovementSpeed() {
        return movement_.getSpeed();
    }

    sf::Vector2f Player::getMovementSnap() const {
        return movement_.snap;
    }

    bool Player::isFacingRight() const {
        return facingRight_;
    }

    PhysicsComponent & Player::getPhysics() {
        return physics_;
    }

    float Player::getEyeDryness() const {
        return eyeDryness_;
    }

    void Player::update() {
        input_.update();
        // physics.verbose = true;
        physics_.update();
        stateManager_.update();
    }
}
