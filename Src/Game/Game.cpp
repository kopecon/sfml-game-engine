//
// Created by Andrew on 29/11/2025.
//

#include "../../Includes/Game/Game.hpp"
#include "../../Includes/World/World.hpp"
#include <unordered_map>


Game::Game() = default;

Game::Game(const std::string &title):
title(title),
video(title)
{}

World* Game::createWorld(std::string name) {
    auto pWorld = std::make_unique<World>(*this, std::move(name));
    auto [it, inserted] = worlds.emplace(pWorld->name, std::move(pWorld));
    pCurrentWorld = it->second.get();
    return it->second.get();
}

World* Game::getWorld(std::string name) {
    const auto NAME = text::up(std::move(name));
    const auto it = worlds.find(NAME);
    if (it == worlds.end())
        return nullptr;
    return it->second.get();
}

void Game::update() {
    time.update();
    // Update entities in the world
    pCurrentWorld->update();
    video.update(pCurrentWorld);
}
