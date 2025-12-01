//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_BACKGROUND_HPP
#define BONK_GAME_BACKGROUND_HPP
#include <SFML/Graphics.hpp>

#include "Scenery.hpp"

class Background final : public Scenery {
public:
    sf::RectangleShape shape{};

    Background();

    explicit Background(sf::Texture &texture, const sf::Vector2u &windowSize);

    void update() override;
};

#endif //BONK_GAME_BACKGROUND_HPP