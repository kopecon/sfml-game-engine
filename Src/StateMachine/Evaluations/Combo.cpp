#include "StateMachine/Evaluations/Combo.hpp"

#include "Engine.hpp"
#include "StateMachine/Actor/Actor.hpp"


namespace state_machine::evaluation::timed {
    Combo::Step::Step(const Step &other)
        : evaluation(other.evaluation ? other.evaluation->clone() : nullptr),
          timing(other.timing),
          precision(other.precision) {
    }

    std::unique_ptr<Combo::Step> Combo::Step::clone() const {
        return std::make_unique<Step>(*this);
    }

    Result Combo::Step::evaluate(const Conductor &conductor) {
        static Status history{};

        const auto [status, score] = evaluation->evaluate(conductor);

        if (status == Status::PASSED && history == Status::FAILED) {
            // Hard cap tolerance growth?
            // Negative tolerance growth?
            timing.tolerance.end += 0.01f;
            timing.tolerance.start -= 0.01f;
        }

        if (status == Status::FAILED) {
            history = status;
        }

        return {status, score};
    }

    Combo::Combo(const std::initializer_list<Step> steps) {
        for (const auto &s: steps) steps_.emplace_back(s.clone());
        reload();
    }

    Combo::Combo(const Combo &other)
        : ClonableEvaluation(other) {
        for (const auto &step: other.steps_) steps_.emplace_back(step->clone());
        reload();
    }

    void Combo::reload() {
        loaded_.clear();
        for (auto &step: steps_) loaded_.emplace_back(step.get());
    }

    float Combo::userTiming(const float start, const float end, const float precision, const float current) {
        // Result belongs in <0,1>.
        // Equals 1 if current in the middle of (end - start).
        // Equals 0 if either current = start || current = end.
        float result = Result::maxScore; // If no end provided, the result is max score.
        if (static_cast<bool>(end)) {
            result = (current - start) * (end - current) / pow(0.5f * (end - start), 2.f);
        }
        result = pow(result, precision);
        return result;
    }

    float Combo::calculateScore(const float sweetSpotsHit) const {
        return sweetSpotsHit / static_cast<float>(steps_.size());
    }

    void Combo::exitAction() noexcept {
        timer_.resetTime();
        timer_.unpause();
        reload();
    }

    void Combo::criterion(const Conductor &conductor) noexcept {
        if (loaded_.empty()) return;

        auto &thisStep = *loaded_.front();
        auto &[t_start, t_end] = thisStep.timing.tolerance;
        const auto opening = thisStep.timing.start + t_start;
        timer_.setDeadline(thisStep.timing.end + t_end);
        const auto [stepStatus, _] = thisStep.evaluate(conductor);

        // 0) INCREASE TIMER
        if (this->isActive()) {
            timer_.tick(conductor.clock().dt());
        }

        // 1) TOOK TOO LONG -> FAILED
        if (timer_.reachedDeadline()) {
            sweetSpotsHit_ = 0.f;
            return this->setStatus(Status::FAILED);
        }

        // 2) STEP FAILED -> FAILED
        if (stepStatus == Status::FAILED) {
            sweetSpotsHit_ = 0.f;
            return this->setStatus(stepStatus);
        }

        // 3) STEP ONGOING -> ONGOING
        if (stepStatus == Status::ONGOING) {
            timer_.pause();
            return;
        }

        // 4) STEP PASSED:
        if (stepStatus == Status::PASSED) {
            // 4A) STEP PASSED TOO SOON -> FAILED
            if (timer_.getTime() < opening) {
                sweetSpotsHit_ = 0.f;
                return this->setStatus(Status::FAILED);
            }

            timer_.unpause();
            // Note: Using opening and deadline which include tolerances here
            // contributes to the difficulty of sweet spot hit. (easier to pass but harder to hit the sweet spot).
            sweetSpotsHit_ += userTiming(opening, timer_.getDeadline(), thisStep.precision, timer_.getTime());
            timer_.resetTime();
            loaded_.pop_front();

            // 4B) STEPS REMAINING -> ONGOING
            if (!loaded_.empty()) {
                loaded_.front()->evaluation->init();
                return this->setStatus(Status::ONGOING);
            }

            score_ = calculateScore(sweetSpotsHit_);
            sweetSpotsHit_ = 0.f;

            // 4C) EVERYTHING PASSED -> PASSED
            return this->setStatus(Status::PASSED);
        }
    }
}
