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
        animationManager(*this),
        stateManager(*this)
        {}

    Player::Player(World &world, const entityID ID, const Controls &controls) :
        Entity(world, ID),
        input(*this, controls),
        physics(*this),
        movement(*this),
        combat(*this),
        animationManager(*this),
        stateManager(*this) {
        buildRender();
    }

    Player::Player(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name)),
        input(*this),
        physics(*this),
        movement(*this),
        combat(*this),
        animationManager(*this),
        stateManager(*this) {
        buildRender();
    }

    Player::Player(World &world, const entityID ID, std::string name, const Controls &controls):
        Entity(world, ID, std::move(name)),
        input(*this, controls),
        physics(*this),
        movement(*this),
        combat(*this),
        animationManager(*this),
        stateManager(*this) {
        buildRender();
    }
    #pragma endregion

    sf::Vector2f Player::getSize() const {
        return shape.getGlobalBounds().size;
    }

    sf::Shape *Player::getShape() {
        return &shape;
    }

    sf::Texture *Player::getTexture() {
        return &game.textures.player;
    }

    sf::Vector2f Player::getPosition() const {
        return shape.getPosition();
    }

    const State<StateSet>* Player::getState() const {
        return stateManager.stateMachine.pCurrentState;
    }

    void Player::buildRender() {
        const auto &texture = game.textures.player;

        auto playerShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(texture.getSize()));

        playerShape->setTexture(&texture);
        playerShape->setTextureRect(sf::IntRect({0, 0}, {32, 32}));
        playerShape->setOrigin(playerShape->getGeometricCenter());

        auto composite = std::make_unique<entity::ShapeComposite>();
        composite->addShape(std::move(playerShape));

        render.addComposite(std::move(composite));
    }

    void Player::initShapeSize() {
        shape.setSize(static_cast<sf::Vector2f>(pTexture->getSize()));
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
        render.update();
        animationManager.update();
    }

    std::string Player::className() const {
        return "Player";
    }
}
