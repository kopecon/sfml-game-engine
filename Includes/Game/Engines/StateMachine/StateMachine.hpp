#ifndef BONK_GAME_STATE_MACHINE_HPP
#define BONK_GAME_STATE_MACHINE_HPP

#include <cassert>
#include <memory>
#include <unordered_map>

#include "Utils/utils.hpp"
#include "Game/Engines/StateMachine/StateMachineContext.hpp"
#include "Game/Engines/StateMachine/State.hpp"


class StateMachine {
public:
    class BaseCore {
    public:
        virtual ~BaseCore() = default;

        BaseCore() = default;

        // GETTERS
        template<EnumSetConcept AnyStateSet>
        bool isInState(typename AnyStateSet::ID id) const {
            if (identifySelf() != utils::identify<AnyStateSet>()) {
                return false;
            }
            return static_cast<std::size_t>(id) == identifyState();
        }

        // DEBUG
        virtual void setVerbose(bool value) = 0;

        // UPDATE
        virtual void update() = 0;

    private:
        // DEBUG
        bool verbose_{false};

        [[nodiscard]] virtual Identifier identifySelf() const = 0;

        [[nodiscard]] virtual std::size_t identifyState() const = 0;
    };

    template<EnumSetConcept StateSet>
    class Core : public BaseCore {
    public:
        using StateT = State<StateSet>;
        using Owner = eval::Evaluable;

#pragma region constructors
        explicit Core(Owner &owner, std::unique_ptr<StateT> defaultState)
            : owner_(owner),
              defaultState_(addState(std::move(defaultState))),
              pCurrentState_(&defaultState_),
              pPreviousState_(pCurrentState_) {
        }
#pragma endregion

        // SETTERS
        template<typename T>
        T &addState(std::unique_ptr<T> state)
            requires std::is_base_of_v<StateT, T> {
            T &addedState = *state;
            auto [it, inserted] = states_.try_emplace(state->handle().id(), std::move(state));
            assert(inserted && "State ID already exists");
            return addedState;
        }

        template<typename T, typename... Args>
        T &createState(Args &&... args)
            requires std::is_base_of_v<StateT, T> {
            auto createdState = std::make_unique<T>(std::forward<Args>(args)...);
            return addState(std::move(createdState));
        }

        void setVerbose(const bool value) override {
            verbose_ = value;
            for (const auto &it: states_) {
                it.second.get()->setVerbose(value);
            }
        }

        // UPDATE
        void update() override {
            auto &currentState = getCurrentState();
            getCurrentState().update();
            checkEdges();
        }

    private:
        // REFERENCE
        Owner &owner_;
        // LIST OF ADDED STATES
        std::unordered_map<typename StateSet::ID, std::unique_ptr<StateT> > states_{};
        // ACCESS
        StateT &defaultState_;
        StateT *pCurrentState_{nullptr};
        StateT *pPreviousState_{nullptr};
        StateT::Edge *pActiveEdge_{nullptr};
        // CONTEXT
        using Context = StateMachineContext<StateSet>;
        Context context_{};
        // DEBUG SETTINGS
        bool verbose_{false};

        // ACTIONS
        void transition(StateHandle<StateSet> next) {
            StateT &nextState = getState(next.id());
            // If next state has no edges generate fallback edge to prevent stuck states
            if (!nextState.hasEdges()) generateFallBackEdge(nextState);
            changeState(nextState);
        }

        void exit(StateT &state) {
            state.onExit();
            setPreviousState(state);
        }

        void enter(StateT &state) {
            state.onEnter(getContext());
            setCurrentState(state);
        }

        void changeState(StateT &next) {
            exit(getCurrentState());
            enter(next);
        }

        void generateFallBackEdge(StateT &state) {
            // Intended as a last resort to prevent stuck states. Temporary solution. Implement better state graph validating.
            state.makeEdge(eval::Conditioned([] { return true; }), defaultState_.handle().id());

#ifndef NDEBUG
            LOG_WARN("Warning: State "
                     + static_cast<std::string>(state.handle().name())
                     + " has no edges. Auto-generated fallback to "
                     + static_cast<std::string>(getCurrentState().handle().name()), true);
#endif
        }

        // SETTERS
        void setCurrentState(StateT &state) {
            if (states_.contains(state.handle().id())) {
                pCurrentState_ = &state;
            } else {
                LOG_ERROR("Attempted to set nonexisting current state: "
                    + static_cast<std::string>(state.handle().name()));
            }
        }

        void setPreviousState(StateT &state) {
            if (states_.contains(state.handle().id())) {
                pPreviousState_ = &state;
            } else {
                LOG_ERROR("Attempted to set nonexisting previous state: "
                    + static_cast<std::string>(state.handle().name()));
            }
        }

        // GETTERS
        [[nodiscard]] Identifier identifySelf() const override {
            return utils::identify<StateSet>();
        }

        [[nodiscard]] std::size_t identifyState() const override {
            return static_cast<std::size_t>(getCurrentState().handle().id());
        }

        [[nodiscard]] StateT &getState(typename StateSet::ID stateID) const {
            auto it = states_.find(stateID);

            if (it == states_.end()) {
                LOG_WARN("Desired state "
                         + static_cast<std::string>(StateSet::name(stateID))
                         + " is not included!", true);
                return getCurrentState();
            }
            return *it->second;
        }

        [[nodiscard]] StateT &getCurrentState() const {
            assert(pCurrentState_); // Should not happen.
            return *pCurrentState_;
        }

        [[nodiscard]] Context getContext() {
            assert(pActiveEdge_); //Gets called only during transition when there is active edge so should not happen
            context_.from = pActiveEdge_->from;
            return context_;
        }

        // UPDATE
        void checkEdges() {
            if (pActiveEdge_) {
                const auto targets = pActiveEdge_->getTargets();
                const auto evaluation = pActiveEdge_->evaluation->evaluate(owner_);

                if (evaluation == evaluation::Evaluation::Result::ONGOING) {
                    LOG_INFO_ONCE(targets + "edge evaluation is ongoing.", verbose_);
                } else if (evaluation == evaluation::Evaluation::Result::PASSED) {
                    LOG_INFO_ONCE(targets + "edge evaluation passed!", verbose_);
                    transition(pActiveEdge_->to);
                    pActiveEdge_ = nullptr;
                } else if (evaluation == evaluation::Evaluation::Result::FAILED) {
                    LOG_WARN_ONCE(targets + "edge evaluation failed!", verbose_);
                    pActiveEdge_ = nullptr;
                }
            } else {
                auto &currentState = getCurrentState();
                if (verbose_ && !currentState.hasEdges())
                    LOG_WARN_ONCE("State: " + static_cast<std::string>(currentState.handle().name()) + " has no edges!\n", verbose_);

                for (const auto &edge: currentState.getEdges()) {
                    if (edge->evaluation->isTriggered(owner_)) {
                        pActiveEdge_ = edge.get();
                        break;
                    }
                }
            }
        }
    };

#pragma region constructors
    explicit StateMachine() = default;

    explicit StateMachine(std::unique_ptr<BaseCore> defaultCore)
        : defaultCore_(std::move(defaultCore)) {
    }
#pragma endregion
    // SETTERS
    template<EnumSetConcept AnyStateSet>
    void swapCore(Core<AnyStateSet> *pCore) {
        pRunningCore_ = pCore;
    }

    void swapCore() {
        if (defaultCore_) {
            pRunningCore_ = defaultCore_.get();
        } else pRunningCore_ = nullptr;
    }

    void setVerbose(const bool value) {
        verbose_ = value;
        if (pRunningCore_) pRunningCore_->setVerbose(value);
    }

    // GETTERS
    template<EnumSetConcept AnyStateSet>
    [[nodiscard]] bool isInState(typename AnyStateSet::ID id) {
        LOG_WARN_ONCE(noRunningCoreMsg_, verbose_);
        if (pRunningCore_)
            return pRunningCore_->isInState<AnyStateSet>(id);
        return false;
    }

    // UPDATE
    void update() const {
        if (!pRunningCore_) {
            LOG_WARN_ONCE(noRunningCoreMsg_, verbose_);
        } else {
            pRunningCore_->update();
        }
    }

private:
    // CORES
    std::unique_ptr<BaseCore> defaultCore_{};
    BaseCore *pRunningCore_{defaultCore_.get()};
    // DEBUG
    bool verbose_{false};
    std::string noRunningCoreMsg_ = "State machine has no running core!";
};


#endif //BONK_GAME_STATE_MACHINE_HPP
