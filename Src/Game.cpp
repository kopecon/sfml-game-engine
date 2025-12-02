//
// Created by Andrew on 29/11/2025.
//

#include "../Includes/Game.hpp"
#include "../Includes/World.hpp"
#include <unordered_map>


Game::Game() = default;

Game::Game(const char *&title):
    title(title),
    video(title) {}

void Game::createWorld(const char* name) {
    auto world = std::make_unique<World>(name);
    world->pGame = this;
    worlds.emplace(world->name, std::move(world));
}

World* Game::getWorld(const char* name) {
    const auto it = worlds.find(name);
    if (it != worlds.end())
        return it->second.get();
    return nullptr;
}


void Game::update() {
    time.update();
    video.update(worlds.begin()->second.get());
}
