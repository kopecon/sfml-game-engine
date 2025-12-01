//
// Created by Andrew on 29/11/2025.
//

#include "../Includes/Game.hpp"
#include "../Includes/World.hpp"


Game::Game() = default;

Game::Game(const char *&title):
    title(title),
    video(title) {}

void Game::update() {
    dt = clock.restart().asSeconds(); // seconds since last frame
    video.update(*pWorld);
}
