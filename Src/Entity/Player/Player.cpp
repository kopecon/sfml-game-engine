#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


namespace player {
    using enum StateSet::ID;

    #pragma region constructors
    Player::Player(World &world, const entityID ID) :
        Entity(world, ID),
        input(*this),
        physics(*this),
        movement(*this),
        combat(*this),
        render(*this),
        animationManager(*this),
        stateManager(*this)
        {}

    Player::Player(World &world, const entityID ID, const Controls &controls) :
        Entity(world, ID),
        input(*this, controls),
        physics(*this),
        movement(*this),
        combat(*this),
        render(*this),
        animationManager(*this),
        stateManager(*this)
        {}

    Player::Player(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name)),
        input(*this),
        physics(*this),
        movement(*this),
        combat(*this),
        render(*this),
        animationManager(*this),
        stateManager(*this)
        {}

    Player::Player(World &world, const entityID ID, std::string name, const Controls &controls):
        Entity(world, ID, std::move(name)),
        input(*this, controls),
        physics(*this),
        movement(*this),
        combat(*this),
        render(*this),
        animationManager(*this),
        stateManager(*this)
        {}
    #pragma endregion

    sf::Vector2f Player::getSize() const {
        return pShape->getGlobalBounds().size;
    }

    sf::Shape *Player::getShape() {
        return pShape;
    }

    sf::Texture *Player::getTexture() {
        return &game.textures.player;
    }

    sf::Vector2f Player::getPosition() const {
        return pShape->getPosition();
    }

    const State<StateSet>* Player::getState() const {
        return stateManager.stateMachine.pCurrentState;
    }

    void Player::init() {
        Entity::init();
        const sf::Vector2f sizeRatio = getWindowToShapeSizeRatio() * height;
        pShape->setScale(sizeRatio);
    }

    void Player::update() {
        input.update();
        physics.update();
        stateManager.update();
        animationManager.update();
    }

    std::string Player::className() const {
        return "Player";
    }
}
