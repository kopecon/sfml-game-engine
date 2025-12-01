//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_GAME_HPP
#define BONK_GAME_GAME_HPP

#include "../Includes/VideoComponent.hpp"
#include "../Includes/AudioComponent.hpp"


class Game {
public:
#pragma region constructors
    Game();
    explicit Game(const char* &title) :
#pragma endregion
    title(title),
    videoComponent(VideoComponent(title))
    {}

    // META DATA
    const char* title{};

    // COMPONENTS
    VideoComponent videoComponent;
    AudioComponent audioComponent;


    sf::Clock clock;
    float dt{};

};

#endif //BONK_GAME_GAME_HPP