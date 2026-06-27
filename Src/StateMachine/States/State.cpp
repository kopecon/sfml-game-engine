#include "StateMachine/States/State.hpp"

#include <ranges>


namespace state_machine::state {
    eval::Status Edge::check(const StateMachine &system, const Conductor *conductor) const {
        if (evaluation_->mode(eval::Mode::PASSIVE)) {
            auto [status, score] = evaluation_->evaluate(system);
            transitionScore_ = score;
            return status;
        }

        if (conductor && evaluation_->mode(eval::Mode::ACTIVE)) {
            auto [status, score] = evaluation_->evaluate(*conductor);
            transitionScore_ = score;
            return status;
        }

        return eval::Status::INACTIVE;
    }

    ID<State> Edge::to() const noexcept {
        return to_;
    }

    void State::addEdge(std::unique_ptr<Edge> edge) {
        edges_.push_back(std::move(edge));
    }

    void State::addEnterAction(std::function<void()> action) {
        enterExtensions_.emplace_back(std::move(action));
    }

    void State::addMainAction(std::function<void()> action) {
        mainExtensions_.emplace_back(std::move(action));
    }

    void State::addExitAction(std::function<void()> action) {
        exitExtensions_.emplace_back(std::move(action));
    }

    void State::enterAction() noexcept {
    }

    void State::mainAction() noexcept {
    }

    void State::exitAction() noexcept {
    }

    void State::quit() noexcept {
        completed_ = true;
    }

    void State::onEnter() noexcept {
        LOG_INFO("Entered: " + this->as_string(), verbose());
        for (auto &extension: enterExtensions_) {
            extension();
        }
        enterAction();
    }

    void State::onUpdate() noexcept {
        for (auto &extension: mainExtensions_) {
            extension();
        }
        mainAction();
    }

    void State::onExit() noexcept {
        LOG_INFO("Exited: " + this->as_string(), verbose());
        exitAction();
        for (auto &extension: std::views::reverse(exitExtensions_)) {
            extension();
        }
    }

    void enterState(State &obj) noexcept {
        obj.onEnter();
    }

    void updateState(State &obj) noexcept {
        obj.onUpdate();
    }

    void exitState(State &obj) noexcept {
        obj.completed_ = false;
        obj.onExit();
    }
} // state_machine
