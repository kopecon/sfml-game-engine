#pragma once

#include <functional>

#include "StateMachine/Evaluations/Evaluation.hpp"


namespace state_machine::evaluation {
    template<typename Derived, typename Target>
    class Conditioned : public ClonableEvaluation<Derived> {
    public:
        [[nodiscard]] bool mode(const Mode target) const noexcept override {
            return target == Mode::PASSIVE;
        }

    protected:
        virtual void condition(const Target &target) {
            assert(false && "Not implemented.");
        }

        void pass() {
            this->setStatus(Status::PASSED);
        }

        void fail() {
            this->setStatus(Status::FAILED);
        }

    private:
        void criterion(const StateMachine &system) noexcept final {
            condition(static_cast<const Target &>(system));
        }
    };

    using Predicate = std::function<bool()>;

    class Predicated final : public ClonableEvaluation<Predicated> {
    public:
        using Evaluation::setStatus;

        explicit Predicated(Predicate predicate);

        [[nodiscard]] bool mode(const Mode target) const noexcept override {
            return target == Mode::PASSIVE;
        }

        void criterion(const StateMachine &system) noexcept override;

        bool operator()() const {
            return predicate_();
        }

    private:
        Predicate predicate_{};
    };
}
