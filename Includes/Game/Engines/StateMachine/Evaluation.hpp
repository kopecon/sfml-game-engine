//
// Created by Andrew on 06/02/2026.
//

#ifndef BONK_GAME_EVALUATION_HPP
#define BONK_GAME_EVALUATION_HPP
#include <functional>

#include "SFML/System/Clock.hpp"


// ALIASES
using Trigger = std::function<bool()>;


class Evaluation {
public:
    virtual ~Evaluation();

    explicit Evaluation(Trigger trigger);

    enum class Result { PASSED, FAILED, ONGOING };

    bool check();

    virtual void start() = 0;

    Result virtual evaluate() = 0;

private:
    Trigger trigger_{};
};


class NoEvaluation final : public Evaluation {
public:
    explicit NoEvaluation(const Trigger &trigger);

    void start() override;

    Result evaluate() override;
};


class TimedEvaluation final : public Evaluation {
public:
    explicit TimedEvaluation(const Trigger &trigger);

    void start() override;

    Result evaluate() override;

private:
    sf::Clock timer{};
};

#endif //BONK_GAME_EVALUATION_HPP
