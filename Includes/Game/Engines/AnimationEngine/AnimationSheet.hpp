#ifndef BONK_GAME_ANIMATION_SHEET_HPP
#define BONK_GAME_ANIMATION_SHEET_HPP

#include "SFML/Graphics/Texture.hpp"


struct AnimationSheet {
    const sf::Texture &texture{};
    const sf::Vector2u frameSize{};
    const unsigned rows{};
    const unsigned columns{};

    explicit AnimationSheet(const sf::Texture &texture, const sf::Vector2u &frameSize);

    explicit AnimationSheet(const sf::Texture &texture, const unsigned &rows, const unsigned &columns);
};


#endif //BONK_GAME_ANIMATION_SHEET_HPP