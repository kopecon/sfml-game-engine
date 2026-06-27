#pragma once

#include <deque>

#include "utils.hpp"
#include "StateMachine/Evaluations/Evaluation.hpp"


namespace state_machine::evaluation::timed {
    class Combo final : public ClonableEvaluation<Combo> {
        struct Step {
            struct Timing {
                struct Tolerance {
                    float start{-0.0f};
                    float end{0.0f};
                };

                Timing() = default;

                Timing(const float start, const float end) : start(start), end(end) {
                }

                float start{0.f};
                float end{0.f}; // If end = 0 -> treat as "inf".

            private:
                friend Combo;
                Tolerance tolerance{};
            };

            template<typename T>
                requires std::derived_from<std::decay_t<T>, Evaluation>
            // For the sake of easier to read syntax.
            // If bugs end up occurring, change to explicit constructor.
            // ReSharper disable once CppNonExplicitConvertingConstructor
            Step(T &&eval); // NOLINT(*-explicit-constructor)

            template<typename T>
                requires std::derived_from<std::decay_t<T>, Evaluation>
            Step(T &&eval, Timing timing, float precision = 1.f);

            Step(const Step &other);

            [[nodiscard]] std::unique_ptr<Step> clone() const;

            [[nodiscard]] Result evaluate(const Conductor &conductor);

            std::unique_ptr<Evaluation> evaluation;
            Timing timing{};
            float precision{1.f}; // The higher the number the bigger punishment for "missed sweet spot".
        };

    public:
        Combo(std::initializer_list<Step> steps);

        Combo(const Combo &other);

    protected:
        float sweetSpotsHit_{0.f};
        std::deque<std::unique_ptr<Step> > steps_{};
        std::deque<Step *> loaded_{};
        utils::Timer timer_{};

        void reload();

        static float userTiming(float start, float end, float precision, float current);

        [[nodiscard]] float calculateScore(float sweetSpotsHit) const;

        void exitAction() noexcept override;

        void criterion(const Conductor &conductor) noexcept override;
    };

    template<typename T> requires std::derived_from<std::decay_t<T>, Evaluation>
    Combo::Step::Step(T &&eval)
        : evaluation(std::make_unique<std::decay_t<T> >(std::forward<T>(eval))) {
    }

    template<typename T> requires std::derived_from<std::decay_t<T>, Evaluation>
    Combo::Step::Step(T &&eval, const Timing timing, const float precision)
        : evaluation(std::make_unique<std::decay_t<T> >(std::forward<T>(eval))),
          timing(timing),
          precision(precision) {
    }
}
