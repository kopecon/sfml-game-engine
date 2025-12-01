//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_GAME_HPP
#define BONK_GAME_GAME_HPP

#include "VideoComponent.hpp"
#include "AudioComponent.hpp"
#include "World.hpp"


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
    VideoComponent video{};  // <- error C3646: 'video': unknown override specifier
    AudioComponent audio{};
    sf::Clock clock{};
    float dt{};

    World *pWorld{};

    void update();
};

#endif //BONK_GAME_GAME_HPP