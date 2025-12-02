//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_GAME_HPP
#define BONK_GAME_GAME_HPP

#include "VideoComponent.hpp"
#include "AudioComponent.hpp"
#include "TimeComponent.hpp"


class World;

class Game {
public:
#pragma region constructors
    Game();
    explicit Game(const char* &title);
#pragma endregion
    // META DATA
    const char* title{};
    // COMPONENTS
    VideoComponent video{};
    AudioComponent audio{};
    TimeComponent time{};
    // WORLDS
    std::unordered_map<std::string, std::unique_ptr<World>> worlds{};

    void createWorld(const char* name);

    World* getWorld(const char* name);

    void update();
};

#endif //BONK_GAME_GAME_HPP