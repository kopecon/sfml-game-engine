//
// Created by Andrew on 06/02/2026.
//

#include "Game/Engines/StateMachine/Evaluation.hpp"

#include "SFML/System/Time.hpp"
#include "Utils/logger.hpp"


Evaluation::~Evaluation() {
}

Evaluation::Evaluation(Trigger trigger) : trigger_(std::move(trigger)) {
}

bool Evaluation::check() {
    const bool triggered = trigger_();
    if (triggered) {
        start();
    }
    return triggered;
}

NoEvaluation::NoEvaluation(const Trigger &trigger) : Evaluation(trigger) {
}

void NoEvaluation::start() {
}

Evaluation::Result NoEvaluation::evaluate() {
    return Result::PASSED;
}

TimedEvaluation::TimedEvaluation(const Trigger &trigger) : Evaluation(trigger) {
}

void TimedEvaluation::start() {
    timer.restart();
    LOG_INFO(std::to_string(timer.getElapsedTime().asSeconds()), true);
}

Evaluation::Result TimedEvaluation::evaluate() {
    const std::string msg = std::to_string(timer.getElapsedTime().asSeconds());
    LOG_INFO(msg, true);
    if (timer.getElapsedTime().asSeconds() > 1.f) {
        return Result::PASSED;
    }
    return Result::ONGOING;
}
