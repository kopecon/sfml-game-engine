//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP

#include <functional>
#include <iostream>
#include <vector>
#include <memory>

#include "../../../../Utils/EnumSet.hpp"

// ALIASES
using Condition = std::function<bool()>;
using Action = std::function<void()>;

template <EnumSetConcept StateSet>
class State {
public:
    struct Edge {
        #pragma region constructors
        Edge() = default;
        explicit Edge(const typename StateSet::ID &id) : next(id) {}
        Edge(Condition condition, const typename StateSet::ID &next) : next(next) {
            this->condition = std::move(condition);
        }
        #pragma endregion

        Condition condition{[]{return false;}};
        StateSet::ID next{};
    };

    #pragma region constructors
    virtual ~State() = default;

    explicit State(const typename StateSet::ID &id) :
        id_(id),
        name_(StateSet::name(id_))
            {}
    #pragma endregion

    // ACTIONS
    virtual void onEnter() {
        if (verbose_) std::cout << "Entered state: " << name_ << "\n";
        if (verbose_ && enterActions_.empty()) std::cout << "State: " << name_ << " has no enter actions!\n";
        for (const auto &action : enterActions_) {
            action();
        }
    }

    virtual void onExit() {
        if (verbose_) std::cout << "Exited state: " << name_ << "\n";
        if (verbose_ && exitActions_.empty()) std::cout << "State: " << name_ << " has no exit actions!\n";
        for (const auto &action : exitActions_) {
            action();
        }
    }

    // SETTERS
    Edge& addEdge(std::unique_ptr<Edge> edge) {
        // Edges are called in the order they were added in. FIFO.
        Edge& edgeRef = *edge;
        edges_.push_back(std::move(edge));
        return edgeRef;
    }

    template<typename... Args>
    Edge& makeEdge(Args&&... args) {
        auto edge = std::make_unique<Edge>(args...);
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

    void connect(const State &state) {
        auto edge = std::make_unique<Edge>(state.id_);
        edges_.push_back(std::move(edge));
    }

    void connect(Condition condition, const State &state) {
        auto edge = std::make_unique<Edge>(std::move(condition), state.id_);
        edges_.push_back(std::move(edge));
    }

    void setVerbose(const bool value) {
        verbose_ = value;
    }

    // GETTERS
    [[nodiscard]] bool hasEdges() const {
        if (edges_.empty()) return false;
        return true;
    }

    typename StateSet::ID getNextStateID() {
        // 0. Warn that state has no edges
        if (edges_.empty()) {
            if (verbose_) std::cout << "State: " << name_ << " has no edges!\n";
        }
        // 1. Choose edge
        for (const auto &edge : this->edges_) {
            if (edge->condition()) {
                return edge->next;
            }
        }
        // 2. No edge conditions met. Staying in this state
        return this->id_;
    }

    [[nodiscard]] typename StateSet::ID getID() const {
        return id_;
    }

    // UPDATE
    virtual void update() {
        if (verbose_ && actions_.empty()) std::cout << "State: " << name_ << " has no actions!\n";
        for (auto const &action : actions_) {
            action();
        }
    }

private:
    // IDENTITY
    typename StateSet::ID id_{};  // Enum value representing the id of the state
    std::string_view name_{};  // String value representing the name of the state
    // EDGES
    std::vector<std::unique_ptr<Edge>> edges_{};  // Connections to other states
    // ACTIONS
    std::vector<Action> actions_{};
    std::vector<Action> enterActions_{};
    std::vector<Action> exitActions_{};
    // DEBUG SETTINGS
    bool verbose_{false};
};

#endif //BONK_GAME_STATE_HPP