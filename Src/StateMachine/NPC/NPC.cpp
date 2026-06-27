#include "StateMachine/NPC/NPC.hpp"


namespace npc {
    NPC::NPC(const Engine &engine) : Actor(engine) {
        addCore(std::make_unique<DecisionCore>(*this, state<Follow>));
    }

    Follow::Follow(Actor &owner) : Decision(owner) {
    }

    void Follow::mainAction() noexcept {
        // TODO: Decouple from hero
        // const auto targetPtr = owner_.engine.world().findFirst<characters::hero::Hero>().lock();
        // const auto ownerPtr = owner_.body().lock();
        // if (!targetPtr or ! ownerPtr) return;

        // const auto &target = *targetPtr;
        // const auto &owner = *ownerPtr;

        // constexpr float offset = 100.f;
        // const auto &targetPos = target.position();
        // const auto &ownerPos = owner.position();
        // const auto place = targetPos.x - offset;

        // auto &controls = owner_.controls();

        // if (target.isInState(state<characters::hero::Running>)) {
        // controls.press(Slot::SLShift);
        // }

        // if (target.isInState(state<characters::hero::Jumping>)) {
        // controls.press(Slot::SW);
        // } else {
        // controls.release(Slot::SW);
        // }

        // if (place > ownerPos.x) {
        // controls.release(Slot::SA);
        // controls.press(Slot::SD);
        // } else if (place < ownerPos.x) {
        // controls.release(Slot::SD);
        // controls.press(Slot::SA);
        // }

        // if (target.isInState(state<characters::hero::Idle>)
        // || utils::math::areClose(ownerPos.x, place, 10.f)) {
        // controls.release(Slot::SA);
        // controls.release(Slot::SD);
        // controls.release(Slot::SLShift);
        // }
    }
} // npc
