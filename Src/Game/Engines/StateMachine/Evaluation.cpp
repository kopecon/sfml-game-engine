#include "Game/Engines/StateMachine/Evaluation.hpp"


evaluation::Evaluation::Result evaluation::Evaluation::evaluate(const Evaluable &actor) {
    return Result::PASSED;
}

evaluation::Conditioned::Conditioned(Condition condition): condition_(std::move(condition)) {
}

bool evaluation::Conditioned::isTriggered(const Evaluable &actor) {
    return condition_();
}

std::unique_ptr<evaluation::Evaluation> evaluation::Conditioned::clone() const {
    return std::make_unique<Conditioned>(*this);
}

evaluation::InputDriven::InputDriven(Slots slots): slots_(std::move(slots)) {
}

evaluation::SlotsPressed::SlotsPressed(const Slots &keys): InputDriven(keys) {
}

bool evaluation::SlotsPressed::isTriggered(const Evaluable &actor) {
    return actor.bindings().slotsPressed(slots_);
}

std::unique_ptr<evaluation::Evaluation> evaluation::SlotsPressed::clone() const {
    return std::make_unique<SlotsPressed>(*this);
}

evaluation::SlotsReleased::SlotsReleased(const Slots &keys): InputDriven(keys) {
}

bool evaluation::SlotsReleased::isTriggered(const Evaluable &actor) {
    return actor.bindings().slotsReleased(slots_);
}

std::unique_ptr<evaluation::Evaluation> evaluation::SlotsReleased::clone() const {
    return std::make_unique<SlotsReleased>(*this);
}

evaluation::SlotsHeld::SlotsHeld(const Slots &keys): InputDriven(keys) {
}

bool evaluation::SlotsHeld::isTriggered(const Evaluable &actor) {
    return actor.bindings().slotsHeld(slots_);
}

std::unique_ptr<evaluation::Evaluation> evaluation::SlotsHeld::clone() const {
    return std::make_unique<SlotsHeld>(*this);
}

evaluation::SlotsNotHeld::SlotsNotHeld(const Slots &keys): InputDriven(keys) {
}

bool evaluation::SlotsNotHeld::isTriggered(const Evaluable &actor) {
    return !actor.bindings().slotsHeld(this->slots_);
}

std::unique_ptr<evaluation::Evaluation> evaluation::SlotsNotHeld::clone() const {
    return std::make_unique<SlotsNotHeld>(*this);
}

evaluation::timed::SlotsHeld::SlotsHeld(const Slots &keys, const float duration): SlotsPressed(keys),
    endTime_(duration) {
}

bool evaluation::timed::SlotsHeld::isTriggered(const Evaluable &actor) {
    if (SlotsPressed::isTriggered(actor)) {
        currentTime_ = 0;
        return true;
    }
    return false;
}

std::unique_ptr<evaluation::Evaluation> evaluation::timed::SlotsHeld::clone() const {
    return std::make_unique<SlotsHeld>(*this);
}

evaluation::Evaluation::Result evaluation::timed::SlotsHeld::evaluate(const Evaluable &actor) {
    const std::string msg = std::to_string(currentTime_);
    LOG_INFO(msg, true);

    currentTime_ += actor.getTime();

    if (actor.bindings().slotsReleased(this->slots_)) {
        if (currentTime_ > endTime_) {
            return Result::PASSED;
        }
        return Result::FAILED;
    }
    return Result::ONGOING;
}
