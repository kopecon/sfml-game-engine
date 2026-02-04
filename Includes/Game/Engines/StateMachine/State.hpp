//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP

#include <functional>
#include <optional>
#include <iostream>
#include <vector>
#include <memory>

#include "Utils/EnumSet.hpp"
#include "Utils/logger.hpp"
#include "Game/Engines/StateMachine/Evaluation.hpp"


// ALIASES
using Action = std::function<void()>;


template<EnumSetConcept StateSet>
class State {
public:
    struct Edge {
#pragma region constructors
        Edge(const typename StateSet::ID &from, Trigger trigger, const typename StateSet::ID &to) : from(from),
            to(to) {
            evaluation = std::make_unique<NoEvaluation>(trigger);
        }

        Edge(const typename StateSet::ID &from, std::unique_ptr<Evaluation> evaluation,
             const typename StateSet::ID &to) : from(from),
                                                evaluation{std::move(evaluation)},
                                                to(to) {
        }
#pragma endregion
        StateSet::ID from{};
        std::unique_ptr<Evaluation> evaluation{};
        StateSet::ID to{};

        // GETTERS
        bool isActive() const {
            return evaluation->check();
        }

        std::string getTargets() {
            auto targets = static_cast<std::string>(StateSet::name(from))
                           + "-"
                           + static_cast<std::string>(StateSet::name(to))
                           + " ";
            return targets;
        }
    };

#pragma region constructors
    virtual ~State() = default;

    explicit State(const typename StateSet::ID &id) : id_(id),
                                                      name_(StateSet::name(id_)) {
    }
#pragma endregion

    // ACTIONS
    virtual void onEnter() {
        LOG_INFO("Entered state: " + name_, verbose_);
        if (enterActions_.empty())
            LOG_INFO_ONCE("State: " + name_ + " has no enter actions!", verbose_);
        for (const auto &action: enterActions_) {
            action();
        }
    }

    virtual void onExit() {
        LOG_INFO("Exited state: " + name_, verbose_);
        if (exitActions_.empty())
            LOG_INFO_ONCE("State: " + name_ + " has no exit actions!", verbose_);
        for (const auto &action: exitActions_) {
            action();
        }
        pNextStateID_ = nullptr;
    }

    // SETTERS
    Edge &addEdge(std::unique_ptr<Edge> edge) {
        // Edges are called in the order they were added in. FIFO.
        Edge &edgeRef = *edge;
        edges_.push_back(std::move(edge));
        return edgeRef;
    }

    template<typename... Args>
    Edge &makeEdge(Args &&... args) {
        auto edge = std::make_unique<Edge>(id_, args...);
        return addEdge(std::move(edge));
    }

    Edge &connect(Trigger trigger, const State &state) {
        auto edge = std::make_unique<Edge>(id_, std::move(trigger), state.id_);
        return addEdge(std::move(edge));
    }

    void addMainAction(Action action) {
        // Actions are called in the order they were added in. FIFO.
        actions_.push_back(std::move(action));
    }

    void addEnterAction(Action action) {
        // Actions are called in the order they were added in. FIFO.
        enterActions_.push_back(std::move(action));
    }

    void addExitAction(Action action) {
        // Actions are called in the order they were added in. FIFO.
        exitActions_.push_back(std::move(action));
    }

    void setVerbose(const bool value) {
        verbose_ = value;
    }

    // GETTERS
    [[nodiscard]] bool hasEdges() const {
        if (edges_.empty()) return false;
        return true;
    }

    [[nodiscard]] typename StateSet::ID getID() const {
        return id_;
    }

    [[nodiscard]] const typename StateSet::ID *getNextStateID() {
        return pNextStateID_;
    }

    // UPDATE
    void update() {
        if (actions_.empty())
            LOG_INFO_ONCE("State: " + name_ + " has no actions!", verbose_);
        for (auto const &action: actions_) {
            action();
        }
        checkEdges();
    }

private:
    // IDENTITY
    typename StateSet::ID id_{}; // Enum value representing the id of the state
    std::string name_{}; // String value representing the name of the state
    // EDGES
    std::vector<std::unique_ptr<Edge> > edges_{}; // Connections to other states
    Edge *pActiveEdge_{nullptr};
    const typename StateSet::ID *pNextStateID_{nullptr};
    // ACTIONS
    std::vector<Action> actions_{};
    std::vector<Action> enterActions_{};
    std::vector<Action> exitActions_{};
    // DEBUG SETTINGS
    bool verbose_{false};

    // UPDATE
    void checkEdges() {
        if (pActiveEdge_) {
            const auto targets = pActiveEdge_->getTargets();
            const auto evaluation = pActiveEdge_->evaluation->evaluate();
            if (evaluation == Evaluation::Result::ONGOING) {
                LOG_INFO(targets + "edge evaluation is ongoing.", verbose_);
            } else if (evaluation == Evaluation::Result::PASSED) {
                pNextStateID_ = &pActiveEdge_->to;
                pActiveEdge_ = nullptr;
                LOG_INFO(targets + "edge evaluation passed!", verbose_);
            } else if (evaluation == Evaluation::Result::FAILED) {
                pActiveEdge_ = nullptr;
                LOG_WARN(targets + "edge evaluation failed!", verbose_);
            }
            return;
        }

        if (verbose_ && edges_.empty())
            LOG_WARN_ONCE("State: " + name_ + " has no edges!\n", verbose_);

        for (const auto &edge: this->edges_) {
            if (edge->isActive()) {
                pActiveEdge_ = edge.get();
            }
        }
    }
};

#endif //BONK_GAME_STATE_HPP
