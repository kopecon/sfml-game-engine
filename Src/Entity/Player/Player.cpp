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

    void Player::setDesiredState(const StateSet::ID state) {
        stateManager_.getEngine().desiredStateID = state;
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
        assert(stateManager_.getEngine().pCurrentState);
        return *stateManager_.getEngine().pCurrentState;
    }

    const State<StateSet>& Player::getPreviousState() const {
        assert(stateManager_.getEngine().pPreviousState);
        return *stateManager_.getEngine().pPreviousState;
    }

    bool Player::isFacingRight() const {
        return facingRight_;
    }

    float Player::getEyeDryness() const {
        return eyeDryness_;
    }

    PhysicsComponent & Player::getPhysics() {
        return physics_;
    }

    MovementComponent & Player::getMovement() {
        return movement_;
    }

    void Player::update() {
        input_.update();
        // physics_.setVerbose(true);
        physics_.update();
        stateManager_.update();
    }
}
