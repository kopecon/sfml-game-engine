//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


using namespace player;

Jumping::Jumping(StateManager *pManager): StateBase(pManager, StateManager::States::JUMPING) {
    addEdge(std::make_unique<Edge>([&](){return !inAir;}, StateManager::States::IDLE));
    addEdge(std::make_unique<Edge>([&](){return !inAir;}, StateManager::States::WALKING));
    addEdge(std::make_unique<Edge>([&](){return !inAir;}, StateManager::States::RUNNING));
    addEdge(std::make_unique<Edge>([&](){return !inAir;}, StateManager::States::STOPPING));
    addEdge(std::make_unique<Edge>([&](){return !inAir;}, StateManager::States::JUMPING));
}

void Jumping::onEnter() {
    StateBase::onEnter();
}

void Jumping::update() {
    if (!inAir) {
        pManager->pPlayer->movement.jump();
        inAir = true;
    }
    else {
        if (pManager->pPlayer->physics.velocity.y == 0) {
            inAir = false;
        }
    }
}
