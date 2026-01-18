//
// Created by Andrew on 18/01/2026.
//

#ifndef BONK_GAME_ANIMATION_SHEET_HPP
#define BONK_GAME_ANIMATION_SHEET_HPP
#include "SFML/Graphics/Texture.hpp"


class AnimationSheet {
public:
    const sf::Texture &texture{};
    const sf::Vector2u frameSize{};
    const unsigned rows{};
    const unsigned columns{};

    explicit AnimationSheet(const sf::Texture &texture, const sf::Vector2u &frameSize) :
        texture(texture),
        frameSize(frameSize),
        rows(texture.getSize().y/frameSize.y),
        columns(texture.getSize().x/frameSize.x)
    {}
    explicit AnimationSheet(const sf::Texture &texture, const unsigned &rows, const unsigned &columns) :
        texture(texture),
        frameSize(sf::Vector2u(
            texture.getSize().x / columns,
            texture.getSize().y / rows
        )),
        rows(rows),
        columns(columns)
    {}
};


#endif //BONK_GAME_ANIMATION_SHEET_HPP