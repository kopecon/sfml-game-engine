//
// Created by Andrew on 23/01/2026.
//

#ifndef BONK_GAME_COLORABLE_HPP
#define BONK_GAME_COLORABLE_HPP
#include "SFML/Graphics/Color.hpp"


class Colorable {
public:
    virtual ~Colorable() = default;
    virtual void applyColor(sf::Color color) = 0;
};


#endif //BONK_GAME_COLORABLE_HPP