//
// Created by Andrew on 13/11/2025.
//

#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


using enum player::StateSet::ID;

#pragma region constructors
player::Player::Player(World &world, const entityID ID) :
    Entity(world, ID),
    input(*this),
    physics(*this),
    movement(*this),
    combat(*this),
    animationManager(*this),
    stateManager(*this)
    {}

player::Player::Player(World &world, const entityID ID, const Controls &controls) :
    Entity(world, ID),
    input(*this, controls),
    physics(*this),
    movement(*this),
    combat(*this),
    animationManager(*this),
    stateManager(*this)
    {}

player::Player::Player(World &world, const entityID ID, std::string name) :
Entity(world, ID, std::move(name)),
    input(*this),
    physics(*this),
    movement(*this),
    combat(*this),
    animationManager(*this),
    stateManager(*this)
    {}

player::Player::Player(World &world, const entityID ID, std::string name, const Controls &controls):
Entity(world, ID, std::move(name)),
    input(*this, controls),
    physics(*this),
    movement(*this),
    combat(*this),
    animationManager(*this),
    stateManager(*this)
    {}
#pragma endregion

sf::Vector2f player::Player::getSize() const {
    return shape.getGlobalBounds().size;
}

sf::Vector2f player::Player::getPosition() const {
    return shape.getPosition();
}

void player::Player::initShapeSize() {

    shape.setSize(static_cast<sf::Vector2f>(pTexture->getSize()));
}

sf::Shape *player::Player::getShape() {
    return &shape;
}

sf::Texture *player::Player::getTexture() {
    return &game.textures.player;
}

void player::Player::init() {
    Entity::init();
    const sf::Vector2f sizeRatio = getWindowToShapeSizeRatio() * height;
    pShape->setScale(sizeRatio);
}

void player::Player::update() {
    input.update();
    physics.update();
    stateManager.update();
    animationManager.update();
}

player::StateSet::ID player::Player::getStateID() const {
    if (stateManager.stateMachine.pCurrentState)
        return stateManager.stateMachine.pCurrentState->stateID;
    return NONE;
}
