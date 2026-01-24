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


template <EnumSetConcept StateSet>
class State {
public:
    struct Edge {
        #pragma region constructors
        Edge() = default;
        explicit Edge(const typename StateSet::ID &id) : next(id) {}
        Edge(std::function<bool()> condition, const typename StateSet::ID &next) : next(next) {
            this->condition = std::move(condition);
        }
        #pragma endregion

        std::function<bool()> condition{};
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
    void addEdge(std::unique_ptr<Edge> edge) {
        edges_.push_back(std::move(edge));
    }

    void addAction(std::function<void()> action) {
        // Actions are called in the order they were added in. FIFO.
        actions_.push_back(std::move(action));
    }

    void addEnterAction(std::function<void()> action) {
        // Actions are called in the order they were added in. FIFO.
        enterActions_.push_back(std::move(action));
    }

    void addExitAction(std::function<void()> action) {
        // Actions are called in the order they were added in. FIFO.
        exitActions_.push_back(std::move(action));
    }

    void connect(const State &state) {
        auto edge = std::make_unique<Edge>(state.id_);
        edges_.push_back(std::move(edge));
    }

    void connect(std::function<bool()> condition, const State &state) {
        auto edge = std::make_unique<Edge>(std::move(condition), state.id_);
        edges_.push_back(std::move(edge));
    }

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
    void setVerbose(const bool value) {
        verbose_ = value;
    }

    // GETTERS
    bool hasEdges() const {
        if (edges_.empty()) return false;
        return true;
    }

    typename StateSet::ID getNext(const typename StateSet::ID &nextStateID) {
        // 0. Warn that state has no edges
        if (edges_.empty()) {
            if (verbose_) std::cout << "State: " << name_ << " has no edges!\n";
        }
        // 1. Choose edge
        for (const auto &edge : this->edges_) {
            // 1.a Edge has a specific condition -> resolve defined condition first
            if (edge->condition) {
                if (edge->condition()) {
                    return edge->next;
                }
            }
            // 1.b Edge has no specific condition
            else {
                if (nextStateID == edge->next) {
                    return edge->next;
                }
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
    // STATE IDENTITY
    typename StateSet::ID id_{};  // Enum value representing the id of the state
    std::string_view name_{};  // String value representing the name of the state
    // EDGES
    std::vector<std::unique_ptr<Edge>> edges_{};  // Connections to other states
    // ACTIONS
    std::vector<std::function<void()>> actions_{};
    std::vector<std::function<void()>> enterActions_{};
    std::vector<std::function<void()>> exitActions_{};
    // DEBUG SETTINGS
    bool verbose_{false};
};

#endif //BONK_GAME_STATE_HPP