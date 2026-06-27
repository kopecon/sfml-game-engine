#include "StateMachine/StateMachine.hpp"

#include <ranges>


namespace state_machine {
    Conductor::~Conductor() = default;

    Conductor::Conductor(const TimeComponent &clock) : clock_(clock) {
    }

    bool Conductor::isActive() const noexcept {
        return !controls_.currentSlots().empty();
    }

    Controls &Conductor::controls() noexcept {
        return controls_;
    }

    const Controls &Conductor::controls() const noexcept {
        return controls_;
    }

    const TimeComponent &Conductor::clock() const noexcept {
        return clock_;
    }

    CoreSwapper::CoreSwapper(auto &cores, const ID<core::Core> id, const std::shared_ptr<core::Core> &newCore)
        : cores_(cores),
          target_id_(id) {
        if (cores_.contains(id)) {
            stashed_ = std::move(cores_[id]);
            cores_[id] = newCore;
        } else {
            LOG_ERROR("Transform target not found!");
        }
    }

    CoreSwapper::~CoreSwapper() {
        if (stashed_) {
            cores_[target_id_] = std::move(stashed_);
        }
    }

    Token<CoreSwapper> StateMachine::swapCore(ID<core::Core> id,
                                              const std::shared_ptr<core::Core> &core) noexcept {
        return Token<CoreSwapper>(cores_, id, core);
    }

    void StateMachine::setConductor(Conductor &conductor) noexcept {
        conductor_ = &conductor;
    }

    void StateMachine::removeConductor() noexcept {
        conductor_ = nullptr;
    }

    const Conductor *StateMachine::conductor() const noexcept {
        if (!conductor_) {
            LOG_WARN_ONCE("Machine has no conductor.", verbose());
        }
        return conductor_;
    }

    void StateMachine::update() const noexcept {
        for (const auto &core: cores_ | std::views::values) {
            core->update();
        }
    }
}
