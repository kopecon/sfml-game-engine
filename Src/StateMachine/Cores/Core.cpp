#include "StateMachine/Cores/Core.hpp"

#include <cassert>

#include "StateMachine/StateMachine.hpp"


namespace state_machine::core {
    const state::State &Core::currentState() const noexcept {
        assert(pCurrentState_ && "No current state.");
        return *pCurrentState_;
    }

    state::State & Core::currentState() noexcept {
        assert(pCurrentState_ && "No current state.");
        return *pCurrentState_;
    }

    Core::Core(StateMachine &system, const std::function<bool()> &runningCondition)
        : system_(system),
          runningCondition_(runningCondition) {
    }

    state::Edge *Core::checkEdges() const noexcept {
        for (const auto &edge: currentState().edges_) {
            const auto status = edge->check(system_, system_.conductor());
            if (status == eval::Status::PASSED) {
                return edge.get();
            }
        }
        return nullptr;
    }

    void Core::enter(state::State &state) noexcept {
        state.setVerbose(verbose());
        enterState(state);
        pCurrentState_ = &state;
    }

    void Core::exit(state::State &state) noexcept {
        exitState(state);
        pPreviousState_ = &state;
    }

    void Core::changeState(state::State &state) noexcept {
        exit(*pCurrentState_);
        enter(state);
    }

    void Core::transition(const state::Edge &edge) {
        try {
            changeState(*states_.at(edge.to()));
        } catch (const std::out_of_range &) {
            LOG_ERROR("Next state is not included in the core.");
        }
    }

    void Core::update() noexcept {
        if (runningCondition_()) {
            if (!initialized_) {
                enter(*pCurrentState_);
                initialized_ = true;
            }

            updateState(*pCurrentState_);
            if (const auto &passedEdge = checkEdges()) {
                transition(*passedEdge);
            }
        }
    }
}
