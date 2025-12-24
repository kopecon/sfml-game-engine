//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


using namespace player;

Jumping::Jumping(StateManager *pManager): StateBase(pManager, StateManager::States::JUMPING) {
    // TODO fix: addEdge(Edge([pManager]{return pManager->engine.conditions.back() == StateManager::States::WALKING;}, StateManager::States::WALKING));
}


void Jumping::update() {
    if (!inAir) {
        pManager->pPlayer->movement.jump();
        inAir = true;
    }
}