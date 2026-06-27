#pragma once

#include <ranges>

#include "EventHandling/Controls.hpp"
#include "StateMachine/Cores/Core.hpp"


class TimeComponent;

namespace actor {
    class Actor;
}

namespace state_machine {
    class StateMachine;


    struct Conductor {
        virtual ~Conductor();

        explicit Conductor(const TimeComponent &clock);

        [[nodiscard]] bool isActive() const noexcept;

        [[nodiscard]] Controls &controls() noexcept;

        [[nodiscard]] const Controls &controls() const noexcept;

        [[nodiscard]] const TimeComponent &clock() const noexcept;

    private:
        Controls controls_{};
        const TimeComponent &clock_;
    };


    struct CoreSwapper {
        CoreSwapper(auto &cores, ID<core::Core> id, const std::shared_ptr<core::Core> &newCore);

        ~CoreSwapper();

    private:
        core::Cores &cores_;
        ID<core::Core> target_id_;
        std::shared_ptr<core::Core> stashed_;
    };


    class StateMachine : public utils::Verbose, public id::Node<StateMachine> {
        friend actor::Actor;

    public:
        StateMachine() = default;

        template<typename C>
            requires(std::derived_from<C, core::Core>)
        void addCore(std::unique_ptr<C> core) noexcept {
            auto &ref = *core;
            LOG_INFO(this->as_string() + " adding core: " + ref.as_string(), verbose());

            auto [it, inserted] = cores_.try_emplace(
                Node<C, core::Core>::NodeID(),
                std::shared_ptr<C>(std::move(core))
            );

            if (!inserted)
                LOG_ERROR("Core not added.");
        }

        template<typename C>
        void removeCore(TypeTag<C>) noexcept;

        [[nodiscard]] Token<CoreSwapper> swapCore(ID<core::Core> id,
                                                  const std::shared_ptr<core::Core> &core) noexcept;


        void setConductor(Conductor &conductor) noexcept;

        void removeConductor() noexcept;

        [[nodiscard]] const Conductor *conductor() const noexcept;

        template<typename T>
        [[nodiscard]] bool isInState(StateType<T> state) const noexcept {
            for (const auto &core: cores_ | std::views::values) {
                if (core->isInState(state)) return true;
            }
            return false;
        }

        void mimic(const StateMachine &other) {
            std::vector<state::State *> otherStates{};

            for (const auto &core: other.cores_ | std::views::values) {
                otherStates.emplace_back(&core->currentState());
            }

            for (const auto &core: cores_ | std::views::values) {
                for (const auto &thisState: core->states_ | std::views::values) {
                    for (const auto &otherState: otherStates) {
                        if (thisState->shared_ids(*otherState).size() > 1) {
                            core->changeState(*thisState);
                        }
                    }
                }
            }
        }

        void update() const noexcept;

    private:
        Conductor *conductor_{nullptr};
        core::Cores cores_{};
    };

    template<typename C>
    void StateMachine::removeCore(TypeTag<C>) noexcept {
        cores_.erase(Node<C>::NodeID());
    }
}

namespace sm = state_machine;
