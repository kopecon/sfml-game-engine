//
// Created by Andrew on 13/11/2025.
//

#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../Includes/Entity/Player/States/StateSet.hpp"
#include "../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../Includes/Game/Engines/StateMachine/State.hpp"
#include "../../../Includes/World/World.hpp"


using enum player::StateSet::ID;

#pragma region constructors
player::Player::Player(std::string name) : Entity(std::move(name)){}
player::Player::Player(std::string name, const Controls &controls) :
Entity(std::move(name)), input(*this, controls), physics(*this), movement(*this), combat(*this), animationManager(*this), stateMachine(this) {
    this->animationManager.engine.animationSheet = {pTexture, {32, 32}};
    this->animationManager.engine.target = &shape;
    stateMachine.addState(std::make_unique<Idle>(this));
    stateMachine.addState(std::make_unique<Jumping>(this));
    stateMachine.addState(std::make_unique<Running>(this));
    stateMachine.addState(std::make_unique<Walking>(this));
    stateMachine.addState(std::make_unique<Stopping>(this));
    stateMachine.addState(std::make_unique<State<StateSet>>(ATTACKING));
    stateMachine.setVerbose();
    stateMachine.getState(IDLE)->addEdge(std::make_unique<State<StateSet>::Edge>(ATTACKING));
    stateMachine.getState(RUNNING)->addEdge(std::make_unique<State<StateSet>::Edge>(ATTACKING));
    animationManager.engine.add(AnimationEntry(IDLE,         2, true));
    animationManager.engine.add(AnimationEntry(WINKING,      2, true));
    animationManager.engine.add(AnimationEntry(WALKING,      4, true));
    animationManager.engine.add(AnimationEntry(RUNNING,      8, true));
    animationManager.engine.add(AnimationEntry(CROUCHING,    6, true));
    animationManager.engine.add(AnimationEntry(JUMPING,      8, false));
    animationManager.engine.add(AnimationEntry(DYING,        8, false));
    animationManager.engine.add(AnimationEntry(DISAPPEARING, 4, false));
    animationManager.engine.add(AnimationEntry(ATTACKING,    8, false));
}
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
    return &pWorld->pGame->textures.player;
}

void player::Player::init() {
    Entity::init();
    const sf::Vector2f sizeRatio = getWindowToShapeSizeRatio() * height;
    pShape->setScale(sizeRatio);
}

void player::Player::update() {
    input.update();
    physics.update();
    stateMachine.update();
    animationManager.update();
}

player::StateSet::ID player::Player::getStateID() const {
    if (stateMachine.pCurrentState)
        return stateMachine.pCurrentState->stateID;
    return NONE;
}
