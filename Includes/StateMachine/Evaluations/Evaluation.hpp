#pragma once

#include "math.hpp"
#include <memory>


namespace state_machine {
    class StateMachine;
    struct Conductor;
}

namespace entity {
    class Entity;
}

namespace actor {
    class Actor;
    struct Context;
}

namespace state_machine::evaluation {
    enum class Status { INACTIVE, ONGOING, PASSED, FAILED };

    enum class Mode { ACTIVE, PASSIVE };

    struct Result {
        static float constexpr maxScore{1.f};
        Status status{};
        float score{};
    };

    class Evaluation {
    public:
        virtual ~Evaluation() = default;

        explicit Evaluation() = default;

        void setStatus(const Status status) noexcept {
            if (status_ != Status::ONGOING && status == Status::ONGOING) onEnter();
            if (utils::math::isAnyOf(status, Status::PASSED, Status::FAILED)) onExit();
            status_ = status;
        }

        virtual void init() noexcept {
        }

        [[nodiscard]] Status getStatus() const noexcept { return status_; }

        [[nodiscard]] Result evaluate(const StateMachine & system) noexcept {
            clear();
            criterion(system);
            return {status_, score_};
        }

        [[nodiscard]] Result evaluate(const Conductor & conductor) noexcept {
            clear();
            criterion(conductor);
            return {status_, score_};
        }

        [[nodiscard]] virtual std::unique_ptr<Evaluation> clone() const noexcept = 0;

        [[nodiscard]] bool isActive() const noexcept {
            return this->getStatus() == Status::ONGOING;
        }

        [[nodiscard]] virtual bool mode(const Mode target) const noexcept {
            return target == Mode::ACTIVE;
        }

    protected:
        float score_{Result::maxScore}; // Maybe move to private

        virtual void enterAction() noexcept {
        }

        virtual void criterion(const StateMachine &system) noexcept {
            assert(false && "Not implemented.");
        }

        virtual void criterion(const Conductor &conductor) noexcept {
            assert(false && "Not implemented.");
        }

        virtual void exitAction() noexcept {
        }

    private:
        Status status_{Status::INACTIVE};

        void clear() {
            if (utils::math::isAnyOf(status_, Status::PASSED, Status::FAILED)) status_ = Status::INACTIVE;
        }

        void onEnter() {
            score_ = Result::maxScore;
            enterAction();
        }

        void onExit() { exitAction(); }
    };

    // --- CRTP CLONING HELPER ---
    template<typename Derived>
    class ClonableEvaluation : public Evaluation {
    public:
        [[nodiscard]] std::unique_ptr<Evaluation> clone() const noexcept override;
    };
}


#pragma region Definitions

namespace state_machine::evaluation {
    // ClonableEvaluation
    template<typename Derived>
    std::unique_ptr<Evaluation> ClonableEvaluation<Derived>::clone() const noexcept {
        return std::make_unique<Derived>(static_cast<const Derived &>(*this));
    }
}

#pragma endregion

// ALIASES
namespace eval = state_machine::evaluation;
