//
// Created by Andrew on 24/12/2025.
//

#ifndef BONK_GAME_STATE_BASE_HPP
#define BONK_GAME_STATE_BASE_HPP

#include <functional>
#include <iostream>
#include <vector>


// THIS IS JUST AN ABSTRACT CLASS
template <typename Manager>
class StateBase {
protected:
    Manager *pManager{nullptr};  // Is the entity which uses the state machine.
public:
    struct Edge {
        #pragma region constructors
        Edge() = default;
        explicit Edge(const typename Manager::States &next) : next(next) {}
        Edge(std::function<bool()> condition, const typename Manager::States &next) : next(next) {
            this->condition = std::move(condition);
        }
        #pragma endregion

        std::function<bool()> condition{};
        Manager::States next{};
    };

    #pragma region constructors
    virtual ~StateBase() = default;
    StateBase(Manager *pManager, const typename Manager::States &stateID) :
    pManager(pManager),
    stateID(stateID)
    {}
    #pragma endregion

    typename Manager::States stateID{};  // Enum class representing possible states
    StateBase *pPreviousState{nullptr};  // Remember from which state you got here
    std::vector<Edge> edges{};  // Connections to other states

    void addEdge(const Edge &edge) {
        edges.push_back(edge);
    }

    virtual void onEnter() {
        // std::cout << pManager->pPlayer->name << " Entered state: " << static_cast<int>(stateID) << "\n";
    }
    virtual void onExit() {
        // std::cout << pManager->pPlayer->name << " Exited state: " << static_cast<int>(stateID) << "\n";
    }

    typename Manager::States next() {
        // 0. Warn that state has no edges
        if (edges.empty()) std::cout << "State: " << static_cast<int>(stateID) << " has no edges!\n";
        // 1. Choose edge
        for (const auto &edge : this->edges) {
            // 1.1 Edge has no specific condition -> condition is just the desired state
            if (!edge.condition) {
                if (pManager->engine.conditions.back() == edge.next) {
                    return edge.next;
                }
            }
            // 1.2 Edge has a specific condition -> resolve defined condition
            else if (edge.condition()) {
                return edge.next;
            }
        }
        return this->stateID;
    }

    virtual void update() = 0;
};


#endif //BONK_GAME_STATE_BASE_HPP