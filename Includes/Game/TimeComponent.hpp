//
// Created by Andrew on 02/12/2025.
//

#ifndef BONK_GAME_TIMECOMPONENT_HPP
#define BONK_GAME_TIMECOMPONENT_HPP
#include "SFML/System/Clock.hpp"


class TimeComponent {
    sf::Clock clock{};
    float dt{};
public:
    float get() const;

    void update();
};


#endif //BONK_GAME_TIMECOMPONENT_HPP