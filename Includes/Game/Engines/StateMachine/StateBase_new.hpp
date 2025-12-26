//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_STATE_BASE_HPP
#define BONK_GAME_STATE_BASE_HPP

#include <functional>
#include <iostream>
#include <vector>


// THIS IS JUST AN ABSTRACT CLASS
template <typename States>
class StateBase_new {
public:
    struct Edge {
        #pragma region constructors
        Edge() = default;
        explicit Edge(const States &next) : next(next) {}
        Edge(std::function<bool()> condition, const States &next) : next(next) {
            this->condition = std::move(condition);
        }
        #pragma endregion

        std::function<bool()> condition{};
        States next{};
    };

    #pragma region constructors
    virtual ~StateBase_new() = default;

    explicit StateBase_new(const States &stateID) : stateID(stateID) {}
    #pragma endregion

    States stateID{};  // Enum class representing possible states
    std::vector<std::unique_ptr<Edge>> edges{};  // Connections to other states

    void addEdge(std::unique_ptr<Edge> edge) {
        edges.push_back(std::move(edge));
    }

    virtual void onEnter() {
        std::cout << " Entered state: " << static_cast<int>(stateID) << "\n";
    }
    virtual void onExit() {
        // std::cout << " Exited state: " << static_cast<int>(stateID) << "\n";
    }

    States next(const States &nextStateID) {
        // 0. Warn that state has no edges
        if (edges.empty()) std::cout << "State: " << static_cast<int>(stateID) << " has no edges!\n";
        // 1. Choose edge
        for (const auto &edge : this->edges) {
            // 1.a Edge has a specific condition -> resolve defined condition first
            if (edge->condition && edge->condition()) {
                    if (nextStateID == edge->next) {
                        return edge->next;
                    }
            }
            // 1.b Edge has no specific condition
            if (nextStateID == edge->next) {
                    return edge->next;
                }
            }
        // 2. No edge conditions met. Staying in this state
        return this->stateID;
    }

    virtual void update() = 0;
};

#endif //BONK_GAME_STATE_BASE_HPP