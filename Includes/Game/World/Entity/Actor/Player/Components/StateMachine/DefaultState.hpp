#ifndef BONK_GAME_DEFAULT_STATE_HPP
#define BONK_GAME_DEFAULT_STATE_HPP

#include "Game/World/Entity/Actor/Player/Player.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultStateSet.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/PlayerState.hpp"
#include "Game/World/Entity/Actor/Player/Components/Render/PlayerSprite.hpp"
#include "Game/Engines/EventHandling/InputBindings.hpp"


using enum player::DefaultStateSet::ID;


namespace player {
    class DefaultState : public PlayerState<DefaultStateSet> {
    public:
        DefaultState(Player &player, const EnumSet<DefaultStateSet>::ID &stateID)
            : PlayerState(player, stateID) {
            addAction(ENTER_ACTION(setStateAnimation));
            addAction(MAIN_ACTION(adjustAnimationFPS));
        }

    protected:
        // COMMON CONDITIONS
        eval::Conditioned idle_{
            [this] { return std::abs(owner_.physics().properties().velocity.x) <= 10.f; }
        };
        eval::Conditioned wink_{
            [this] { return player().stats().eyeDryness >= 100; }
        };

        // ASSIGN SLOTS
        InputSlot left_ = InputSlot::S2;
        InputSlot right_ = InputSlot::S4;
        InputSlot boost_ = InputSlot::S5;
        InputSlot concentration_ = InputSlot::S7;

        // COMMON EVALUATIONS
        eval::SlotsNotHeld brake_{{{left_}, {right_}}};

        eval::SlotsHeld walk_{{{left_}, {right_}}};

        eval::SlotsHeld run_{{{boost_, left_}, {boost_, right_}}};

        eval::SlotsHeld stop_{{{left_, right_}}};

        eval::SlotsHeld jump_{{{InputSlot::S1}}};

        eval::SlotsReleased attack_{{{InputSlot::S6}}};

        eval::timed::SlotsHeld concentrate_{{{concentration_}}, 0.5f};

        AnimationEngine<DefaultStateSet> &animator() {
            return player().getRenderManager().getMainSprite().getAnimator();
        }

        virtual void setStateAnimation() {
            animator().setAnimation(handle().id());
        }

        virtual void adjustAnimationFPS() {
        }
    };
}

#endif //BONK_GAME_DEFAULT_STATE_HPP
