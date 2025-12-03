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
    // WORLDS
    std::unordered_map<std::string, std::unique_ptr<World>> worlds{};
public:
#pragma region constructors
    Game();
    explicit Game(const std::string &title);
#pragma endregion
    // META DATA
    const std::string title{};
    // COMPONENTS
    VideoComponent video{};
    AudioComponent audio{};
    TimeComponent time{};


    World* createWorld(const std::string &name);

    World* getWorld(const std::string &name);

    void update();
};

#endif //BONK_GAME_GAME_HPP