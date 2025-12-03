//
// Created by Andrew on 02/12/2025.
//

#ifndef BONK_GAME_TIMECOMPONENT_HPP
#define BONK_GAME_TIMECOMPONENT_HPP
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"


class TimeComponent {
public:
    sf::Clock clock{};
    float dt{};

    void update() {
        dt = clock.restart().asSeconds(); // seconds since last frame
    }
};


#endif //BONK_GAME_TIMECOMPONENT_HPP