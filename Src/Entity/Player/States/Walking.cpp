//
// Created by Andrew on 07/12/2025.
//
#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"


using namespace player;


Walking::Walking(StateManager *stateManager): StateBase(stateManager, StateManager::States::WALKING) {
    addEdge(Edge(StateManager::States::IDLE));
    addEdge(Edge(StateManager::States::JUMPING));
    addEdge(Edge(StateManager::States::STOPPING));
    addEdge(Edge(StateManager::States::RUNNING));
}

void Walking::update() {
    pManager->pPlayer->movement.speed = pManager->pPlayer->movement.walkingSpeed;
    pManager->pPlayer->movement.walk();
}