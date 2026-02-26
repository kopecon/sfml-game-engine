#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP

#include <functional>
#include <vector>
#include <optional>
#include <memory>

#include "Game/Engines/StateMachine/StateMachineContext.hpp"
#include "Game/Engines/StateMachine/StateHandle.hpp"
#include "Game/Engines/StateMachine/Evaluation.hpp"


// ALIASES
using Action = std::function<void()>;
#define ACTION(method) [this]{this->method();}

enum class ActionTypes { ENTER, MAIN, EXIT };

#define ENTER_ACTION(method) {ActionTypes::ENTER, [this]{this->method();}}
#define MAIN_ACTION(method)  {ActionTypes::MAIN , [this]{this->method();}}
#define EXIT_ACTION(method)  {ActionTypes::EXIT , [this]{this->method();}}


namespace actor {
    class Actor;
}

template<EnumSetConcept StateSet>
class State {
public:
    using Handle = StateHandle<StateSet>;
    using Target = actor::Actor;

protected:
    using Context = StateMachineContext<StateSet>;

public:
    struct Edge {
#pragma region constructors
        Edge(const typename StateSet::ID &from, std::unique_ptr<eval::Evaluation> eval, const typename StateSet::ID &to)
            : from(from),
              evaluation(std::move(eval)),
              to(to) {
        }
#pragma endregion
        Handle from{};
        std::unique_ptr<eval::Evaluation> evaluation;
        Handle to{};

        [[nodiscard]] std::string getTargets() const {
            auto targets = static_cast<std::string>(from.name())
                           + "-"
                           + static_cast<std::string>(to.name())
                           + " ";
            return targets;
        }
    };

#pragma region constructors
    virtual ~State() = default;

    explicit State(Target &target, const typename StateSet::ID &id)
        : target_(target),
          handle_(id) {
    }
#pragma endregion

    // ACTIONS
    virtual void onEnter(const Context context) {
        context_ = context;
        LOG_INFO("Entered state: " + static_cast<std::string>(handle_.name()), verbose_);
        if (enterActions_.empty())
            LOG_INFO_ONCE("State: " + static_cast<std::string>(handle_.name()) + " has no enter actions!", verbose_);
        for (const auto &action: enterActions_) {
            action();
        }
    }

    virtual void onExit() {
        LOG_INFO("Exited state: " + static_cast<std::string>(handle_.name()), verbose_);
        if (exitActions_.empty())
            LOG_INFO_ONCE("State: " + static_cast<std::string>(handle_.name()) + " has no exit actions!", verbose_);
        for (const auto &action: exitActions_) {
            action();
        }
    }

    // SETTERS
    Edge &addEdge(std::unique_ptr<Edge> edge) {
        // Edges are called in the order they were added in. FIFO.
        Edge &edgeRef = *edge;
        edges_.push_back(std::move(edge));
        return edgeRef;
    }

    template<typename EvaluationType>
    Edge &makeEdge(EvaluationType &&eval, typename StateSet::ID id) {
    using EvalDecayed = std::decay_t<EvaluationType>;

    std::unique_ptr<eval::Evaluation> pEvaluation;
    // CLONE EVALUATION
    if constexpr (std::derived_from<EvalDecayed, eval::Evaluation>) {
    pEvaluation = eval.clone();
    }
    // TAKE OWNERSHIP OF IN-PLACE CREATED EVALUATION
    else if constexpr (EvaluationUniquePtr<EvalDecayed>) {
    pEvaluation = std::forward<EvaluationType>(eval);
    }
    // INVALID TYPE OF EVALUATION
    else {
    static_assert(std::derived_from<EvalDecayed, eval::Evaluation>,
    "Invalid type passed to makeEdge");
    }

    auto edge = std::make_unique<Edge>(handle_.id(), std::move(pEvaluation), id);
    return addEdge(std::move(edge));
    }

    template<typename EvaluationType>
    Edge &connect(EvaluationType &&eval, const State &state) {
        return makeEdge(std::forward<EvaluationType>(eval), state.handle());
    }

    void addMainAction(Action action) {
        // Actions are called in the order they were added in. FIFO.
        mainActions_.push_back(std::move(action));
    }

    void addEnterAction(Action action) {
        // Actions are called in the order they were added in. FIFO.
        enterActions_.push_back(std::move(action));
    }

    void addExitAction(Action action) {
        // Actions are called in the order they were added in. FIFO.
        exitActions_.push_back(std::move(action));
    }

    void addAction(const std::pair<ActionTypes, Action> &action) {
        if (action.first == ActionTypes::ENTER) {
            addEnterAction(action.second);
        } else if (action.first == ActionTypes::MAIN) {
            addMainAction(action.second);
        } else if (action.first == ActionTypes::EXIT) {
            addExitAction(action.second);
        }
    }

    void setVerbose(const bool value) {
        verbose_ = value;
    }

    // GETTERS
    [[nodiscard]] bool hasEdges() const {
        return !edges_.empty();
    }

    [[nodiscard]] const Handle &handle() const {
        return handle_;
    }

    [[nodiscard]] const std::vector<std::unique_ptr<Edge>> &getEdges() const {
        return edges_;
    }

    // UPDATE
    void update() const {
        if (mainActions_.empty())
            LOG_INFO_ONCE("State: " + static_cast<std::string>(handle_.name()) + " has no actions!", verbose_);
        for (auto const &action: mainActions_) {
            action();
        }
    }

protected:
    // REFERENCE
    Target &target_;
    // CONTEXT
    Context context_{};

private:
    // IDENTITY
    const Handle handle_;
    // EDGES
    std::vector<std::unique_ptr<Edge> > edges_{}; // Connections to other states
    // ACTIONS
    std::vector<Action> mainActions_{};
    std::vector<Action> enterActions_{};
    std::vector<Action> exitActions_{};
    // DEBUG SETTINGS
    bool verbose_{false};
};

#endif //BONK_GAME_STATE_HPP
