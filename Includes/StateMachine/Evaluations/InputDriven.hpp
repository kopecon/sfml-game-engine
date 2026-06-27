#pragma once

#include "utils.hpp"
#include "EventHandling/Controls.hpp"
#include "StateMachine/Evaluations/Evaluation.hpp"


namespace state_machine::evaluation {
    template<typename Derived>
    class InputDriven : public ClonableEvaluation<Derived> {
    protected:
        using Slots = Controls::ControlSlots;
        Slots slots_{};

    public:
        explicit InputDriven(Slot slot);

        explicit InputDriven(Slots slots);
    };

    class SlotsPressed : public InputDriven<SlotsPressed> {
    public:
        using InputDriven::InputDriven;

    protected:
        void criterion(const Conductor &conductor) noexcept override;
    };

    class SlotsReleased final : public InputDriven<SlotsReleased> {
    public:
        using InputDriven::InputDriven;

    protected:
        void criterion(const Conductor &conductor) noexcept override;
    };


    class SlotsHeld : public InputDriven<SlotsHeld> {
    public:
        using InputDriven::InputDriven;

    protected:
        void criterion(const Conductor &conductor) noexcept override;
    };

    class SlotsNotHeld final : public InputDriven<SlotsNotHeld> {
    public:
        using InputDriven::InputDriven;

    protected:
        void criterion(const Conductor &conductor) noexcept override;
    };

    namespace timed {
        class SlotsHeld final : public evaluation::SlotsHeld {
        public:
            SlotsHeld(Slot slot, float duration);

            [[nodiscard]] std::unique_ptr<Evaluation> clone() const noexcept override;

        protected:
            void exitAction() noexcept override { timer_.resetTime(); }

            void criterion(const Conductor &conductor) noexcept override;

        private:
            utils::Timer timer_{};
        };
    }

    namespace strict {
        class SlotsPressed final : public evaluation::SlotsPressed {
        public:
            using evaluation::SlotsPressed::SlotsPressed;

            [[nodiscard]] std::unique_ptr<Evaluation> clone() const noexcept override;

        protected:
            bool slotsCleared_{false};

            void init() noexcept override;

            void exitAction() noexcept override;

            void criterion(const Conductor &conductor) noexcept override;
        };
    }

#pragma region Definitions
    template<typename Derived>
    InputDriven<Derived>::InputDriven(Slot slot) : slots_(Slots{{slot}}) {
    }

    template<typename Derived>
    InputDriven<Derived>::InputDriven(Slots slots) : slots_(std::move(slots)) {
    }
#pragma endregion
}
