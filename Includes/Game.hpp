//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_GAME_HPP
#define BONK_GAME_GAME_HPP

#include "../Includes/VideoComponent.hpp"


class Game {
public:
    Game() : videoComponent(VideoComponent(title)){};
    const std::string title{"Bonk Game"};
    VideoComponent videoComponent;
};


#endif //BONK_GAME_GAME_HPP