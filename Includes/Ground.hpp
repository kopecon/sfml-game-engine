//
// Created by Andrew on 27/11/2025.
//

#ifndef BONK_GAME_GROUND_HPP
#define BONK_GAME_GROUND_HPP

#include "Scenery.hpp"


class Ground final : public Scenery {
public:
    sf::Shape *shapes[2]{};
    sf::Texture *pTexture{};
    sf::Texture *pTextureTop{};
    sf::RectangleShape body{};
    sf::RectangleShape top{};

    Ground();

    Ground(sf::Texture &bodyTexture, sf::Texture &topTexture, const sf::Vector2u &windowSize);

    void setGroundLevel();

    void update() override;
};


#endif //BONK_GAME_GROUND_HPP