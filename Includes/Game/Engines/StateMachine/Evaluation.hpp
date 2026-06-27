#ifndef BONK_GAME_EVALUATION_HPP
#define BONK_GAME_EVALUATION_HPP

#include <functional>
#include <memory>
#include <utility>

#include "Game/Engines/EventHandling/InputBindings.hpp"
#include "Game/Engines/StateMachine/Evaluable.hpp"
#include "Utils/logger.hpp"


// ALIASES
using Condition = std::function<bool()>;


namespace evaluation {
    class Evaluation {
    public:
        virtual ~Evaluation() = default;

        explicit Evaluation() = default;

        enum class Result { PASSED, FAILED, ONGOING };

        // GETTERS
        [[nodiscard]] virtual bool isTriggered(const Evaluable &actor) = 0;

        [[nodiscard]] virtual std::unique_ptr<Evaluation> clone() const = 0;

        Result virtual evaluate(const Evaluable &actor);
    };

    class Conditioned final : public Evaluation {
    public:
        explicit Conditioned(Condition condition);

        [[nodiscard]] bool isTriggered(const Evaluable &actor) override;

        [[nodiscard]] std::unique_ptr<Evaluation> clone() const override;

    private:
        Condition condition_;
    };

    class InputDriven : public Evaluation {
    protected:
        using Slots = InputBindings::SlotGroup;

    public:
        explicit InputDriven(Slots slots);

    protected:
        Slots slots_{};
    };


    class SlotsPressed : public InputDriven {
    public:
        explicit SlotsPressed(const Slots &keys);

        [[nodiscard]] bool isTriggered(const Evaluable &actor) override;

        [[nodiscard]] std::unique_ptr<Evaluation> clone() const override;
    };


    class SlotsReleased final : public InputDriven {
    public:
        explicit SlotsReleased(const Slots &keys);

        [[nodiscard]] bool isTriggered(const Evaluable &actor) override;

        [[nodiscard]] std::unique_ptr<Evaluation> clone() const override;
    };


    class SlotsHeld final : public InputDriven {
    public:
        explicit SlotsHeld(const Slots &keys);

        [[nodiscard]] bool isTriggered(const Evaluable &actor) override;

        [[nodiscard]] std::unique_ptr<Evaluation> clone() const override;
    };


    class SlotsNotHeld final : public InputDriven {
    public:
        explicit SlotsNotHeld(const Slots &keys);

        [[nodiscard]] bool isTriggered(const Evaluable &actor) override;

        [[nodiscard]] std::unique_ptr<Evaluation> clone() const override;
    };

    namespace timed {
        class SlotsHeld final : public SlotsPressed {
        public:
            SlotsHeld(const Slots &keys, const float duration);

            [[nodiscard]] bool isTriggered(const Evaluable &actor) override;

            [[nodiscard]] std::unique_ptr<Evaluation> clone() const override;

            Result evaluate(const Evaluable &actor) override;

        private:
            float currentTime_{}; // In seconds
            const float endTime_{}; // In seconds
        };
    }
}

// ALIASES
namespace eval = evaluation;


// CONCEPT
template<typename T>
concept EvaluationUniquePtr =
        requires
        {
            typename T::element_type;
            requires std::derived_from<typename T::element_type, eval::Evaluation>;
        };

#endif //BONK_GAME_EVALUATION_HPP
