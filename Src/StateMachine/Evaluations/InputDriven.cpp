#include "StateMachine/Evaluations/InputDriven.hpp"

#include "StateMachine/StateMachine.hpp"
#include "Time/TimeComponent.hpp"


namespace state_machine::evaluation {
    void SlotsPressed::criterion(const Conductor &conductor) noexcept {
        if (conductor.controls().pressed(this->slots_)) this->setStatus(Status::PASSED);
    }


    void SlotsReleased::criterion(const Conductor &conductor) noexcept {
        if (conductor.controls().released(this->slots_)) this->setStatus(Status::PASSED);
    }


    void SlotsHeld::criterion(const Conductor &conductor) noexcept {
        if (conductor.controls().holds(this->slots_)) {
            this->setStatus(Status::PASSED);
        }
    }


    void SlotsNotHeld::criterion(const Conductor &conductor) noexcept {
        if (!conductor.controls().holds(this->slots_)) this->setStatus(Status::PASSED);
    }

    namespace timed {
        SlotsHeld::SlotsHeld(const Slot slot, const float duration)
            : evaluation::SlotsHeld(slot) {
            timer_.setDeadline(duration);
        }


        std::unique_ptr<Evaluation> SlotsHeld::clone() const noexcept {
            return std::make_unique<SlotsHeld>(*this);
        }


        void SlotsHeld::criterion(const Conductor &conductor) noexcept {
            if (this->getStatus() != Status::ONGOING) {
                if (conductor.controls().holds(this->slots_)) this->setStatus(Status::ONGOING);
                else this->setStatus(Status::INACTIVE);
            }
            if (this->isActive()) {
                timer_.tick(conductor.clock().dt());
                if (conductor.controls().released(this->slots_)) {
                    this->setStatus(timer_.reachedDeadline() ? Status::PASSED : Status::FAILED);
                }
            }
        }
    }

    namespace strict {
        std::unique_ptr<Evaluation> SlotsPressed::clone() const noexcept {
            return std::make_unique<SlotsPressed>(*this);
        }


        void SlotsPressed::init() noexcept {
            slotsCleared_ = false;
        }


        void SlotsPressed::exitAction() noexcept { slotsCleared_ = false; }


        void SlotsPressed::criterion(const Conductor &conductor) noexcept {
            const auto currentSlots = conductor.controls().currentSlots();

            if (currentSlots.empty()) slotsCleared_ = true;

            if (slotsCleared_ && !currentSlots.empty()) {
                for (const auto &slots: this->slots_) {
                    if (currentSlots == slots) {
                        this->setStatus(Status::PASSED);
                        return;
                    }
                }
                this->setStatus(Status::FAILED);
            }
        }
    }
}
