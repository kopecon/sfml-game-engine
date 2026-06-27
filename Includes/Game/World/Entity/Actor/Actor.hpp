#ifndef BONK_GAME_ACTOR_HPP
#define BONK_GAME_ACTOR_HPP

#include "Game/Game.hpp"
#include "Game/Engines/EventHandling/InputBindings.hpp"
#include "Game/Engines/StateMachine/Evaluable.hpp"
#include "Game/World/Entity/Entity.hpp"
#include "Game/Engines/StateMachine/StateMachine.hpp"


namespace actor {
    class Actor : public entity::Entity, public eval::Evaluable {
    public:
        Actor(World &world, entityID id, const std::string &name,
              std::unique_ptr<StateMachine::BaseCore> defaultCore);

        // GETTERS
        float getTime() const override;

        [[nodiscard]] StateMachine &getStateMachine();

        [[nodiscard]] const StateMachine &getStateMachine() const;

        [[nodiscard]] InputBindings &bindings() override;

        [[nodiscard]] const InputBindings &bindings() const override;

        [[nodiscard]] static std::string getClassName();

        void update() override;

    protected:
        // COMPONENTS
        InputBindings bindings_{game.getInput()};
        StateMachine stateMachine_{};
    };
}


#endif //BONK_GAME_ACTOR_HPP
