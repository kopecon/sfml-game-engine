//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP

#include <functional>
#include <iostream>
#include <vector>
#include <memory>

#include "StateSetBase.hpp"

class Entity;


template <StateSetConcept StateSet>
class State {
public:
    struct Edge {
        #pragma region constructors
        Edge() = default;
        explicit Edge(const typename StateSet::ID &next) : next(next) {}
        Edge(std::function<bool()> condition, const typename StateSet::ID &next) : next(next) {
            this->condition = std::move(condition);
        }
        #pragma endregion

        std::function<bool()> condition{};
        StateSet::ID next{};
    };

    #pragma region constructors
    virtual ~State() = default;

    explicit State(const typename StateSet::ID &stateID) : stateID(stateID), name(StateSet::name(stateID)) {}
    #pragma endregion

    // STATE IDENTITY
    typename StateSet::ID stateID{};  // Enum value representing the id of the state
    std::string_view name{};  // String value representing the name of the state
    // DEBUG SETTINGS
    bool verbose{false};

    void addEdge(std::unique_ptr<Edge> edge) {
        edges.push_back(std::move(edge));
    }

    void addAction(std::function<void()> action) {
        // Actions are called in the order they were added in. FIFO.
        actions.push_back(std::move(action));
    }
    void addEnterAction(std::function<void()> action) {
        // Actions are called in the order they were added in. FIFO.
        enterActions.push_back(std::move(action));
    }
    void addExitAction(std::function<void()> action) {
        // Actions are called in the order they were added in. FIFO.
        exitActions.push_back(std::move(action));
    }

    typename StateSet::ID next(const typename StateSet::ID &nextStateID) {
        // 0. Warn that state has no edges
        if (verbose && edges.empty()) std::cout << "State: " << name << " has no edges!\n";
        // 1. Choose edge
        for (const auto &edge : this->edges) {
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
        return this->stateID;
    }

    virtual void onEnter() {
        if (verbose) std::cout << "Entered state: " << name << "\n";
        if (verbose && enterActions.empty()) std::cout << "State: " << name << " has no enter actions!\n";
        for (const auto &action : enterActions) {
            action();
        }
    }
    virtual void onExit() {
        if (verbose) std::cout << "Exited state: " << name << "\n";
        if (verbose && exitActions.empty()) std::cout << "State: " << name << " has no exit actions!\n";
        for (const auto &action : exitActions) {
            action();
        }
    }

    virtual void update() {
        if (verbose && actions.empty()) std::cout << "State: " << name << " has no actions!\n";
        for (auto const &action : actions) {
            action();
        }
    };

private:
    std::vector<std::unique_ptr<Edge>> edges{};  // Connections to other states
    std::vector<std::function<void()>> actions{};  // Connections to other states
    std::vector<std::function<void()>> enterActions{};  // Connections to other states
    std::vector<std::function<void()>> exitActions{};  // Connections to other states
};

#endif //BONK_GAME_STATE_HPP