//
// Created by Andrew on 29/11/2025.
//

#include "../Includes/Game.hpp"
#include "../Includes/World.hpp"
#include <unordered_map>

#include "../Includes/utils.hpp"


Game::Game() = default;

Game::Game(const std::string &title):
    title(title),
    video(title) {}

World* Game::createWorld(const std::string &name) {
    auto pWorld = std::make_unique<World>(name);
    pWorld->pGame = this;
    worlds.emplace(pWorld->name, std::move(pWorld));
    return getWorld(name);
}

World* Game::getWorld(std::string name) {
    string::up(name);
    const auto it = worlds.find(name);
    if (it != worlds.end())
        return it->second.get();
    return nullptr;
}


void Game::update() {
    time.update();
    video.update(worlds.begin()->second.get());
}
