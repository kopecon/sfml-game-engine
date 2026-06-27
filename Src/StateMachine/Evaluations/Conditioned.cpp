#include "StateMachine/Evaluations/Conditioned.hpp"


namespace state_machine::evaluation {
    Predicated::Predicated(Predicate predicate) : predicate_(std::move(predicate)) {
    }

    void Predicated::criterion(const StateMachine &system) noexcept {
        if (predicate_()) this->setStatus(Status::PASSED);
    }
}
