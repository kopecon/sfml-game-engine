//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/States/State.hpp"


State::~State() {
}

State::State(std::string name) : name(std::move(name)) {
}

State::State(Player &player, std::string name): pPlayer(&player), name(std::move(name)) {}
