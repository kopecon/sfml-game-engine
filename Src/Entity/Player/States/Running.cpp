//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"


using namespace player;

Running::Running(StateManager *stateManager): StateBase(stateManager, StateManager::States::RUNNING) {
    addEdge(Edge(StateManager::States::WALKING));
    addEdge(Edge(StateManager::States::JUMPING));
    addEdge(Edge(StateManager::States::STOPPING));
    addEdge(Edge(StateManager::States::IDLE));
}


void Running::update() {
    pManager->pPlayer->movement.speed = pManager->pPlayer->movement.runningSpeed;
    pManager->pPlayer->movement.walk();
}