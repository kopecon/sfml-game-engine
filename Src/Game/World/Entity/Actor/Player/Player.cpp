#include "Game/World/Entity/Actor/Player/Player.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultCore.hpp"


namespace player {
    using enum DefaultStateSet::ID;

#pragma region constructors
    Player::Player(World &world, const entityID ID, const std::string &name)
        : Actor(world, ID, name, std::make_unique<DefaultCore>(*this)) {
        using enum InputSlot;
        Actor::bindings().bind(S1, sf::Keyboard::Scancode::W);
        Actor::bindings().bind(S2, sf::Keyboard::Scancode::A);
        Actor::bindings().bind(S3, sf::Keyboard::Scancode::S);
        Actor::bindings().bind(S4, sf::Keyboard::Scancode::D);
        Actor::bindings().bind(S5, sf::Keyboard::Scancode::LShift);
        Actor::bindings().bind(S6, sf::Keyboard::Scancode::F);
        Actor::bindings().bind(S7, sf::Keyboard::Scancode::C);
    }
#pragma endregion

    std::string Player::getClassName() {
        return "Player";
    }

    Stats & Player::stats() {
        return stats_;
    }

    RenderManager &Player::getRenderManager() {
        return renderManager_;
    }

    void Player::update() {
        Actor::update();
        physics_.update();
    }
}
