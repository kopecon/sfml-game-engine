#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"


namespace player {
    using enum StateSet::ID;

    #pragma region constructors

    Player::Player(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name)),
        input(*this),
        physics(*this),
        movement(*this),
        combat(*this),
        renderManager(*this),
        animationManager(*this),
        stateManager(*this) {
    }

    Player::Player(World &world, const entityID ID, std::string name, const Controls &controls) :
        Entity(world, ID, std::move(name)),
        input(*this, controls),
        physics(*this),
        movement(*this),
        combat(*this),
        renderManager(*this),
        animationManager(*this),
        stateManager(*this) {
    }
    #pragma endregion

    std::string Player::getClassName() {
        return "Player";
    }

    sf::Vector2f Player::getCharacterSize() const {
        return {height, width};
    }

    sf::Vector2f Player::getRenderSize() const {
        return render.getGlobalBounds().size;
    }

    const State<StateSet>& Player::getState() const {
        return *stateManager.stateMachine.pCurrentState;
    }

    sf::Sprite & Player::getSprite() const {
        //TODO: implement propper shape accessing
        return *render.getSprite();
    }

    void Player::update() {
        input.update();
        // physics.verbose = true;
        physics.update();
        stateManager.update();
        animationManager.update();
    }
}
