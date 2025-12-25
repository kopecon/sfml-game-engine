//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"

#include "../../../../Includes/Entity/Player/StateManager.hpp"


using namespace player;

Idle::Idle(StateManager *stateManager) :
StateBase(stateManager, StateManager::States::IDLE) {
    addEdge(std::make_unique<Edge>(StateManager::States::WALKING));
    addEdge(std::make_unique<Edge>(StateManager::States::JUMPING));
    addEdge(std::make_unique<Edge>(StateManager::States::STOPPING));
    addEdge(std::make_unique<Edge>(StateManager::States::RUNNING));
}

void Idle::update() {
    pManager->pPlayer->movement.brake();
}