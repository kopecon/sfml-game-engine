//
// Created by Andrew on 08/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"


using namespace player;

Stopping::Stopping(StateManager *stateManager): StateBase(stateManager, StateManager::States::STOPPING) {
    addEdge(Edge(StateManager::States::WALKING));
    addEdge(Edge(StateManager::States::JUMPING));
    addEdge(Edge(StateManager::States::IDLE));
    addEdge(Edge(StateManager::States::RUNNING));
}


void Stopping::update() {
    pManager->pPlayer->movement.brake();
}