//
// Created by Andrew on 13/11/2025.
//

#ifndef BONK_GAME_BACKGROUND_HPP
#define BONK_GAME_BACKGROUND_HPP
#include <SFML/Graphics.hpp>
#include "../Includes/Camera.hpp"

namespace scenery {
    class Ground {
    public:
        sf::Vector2f size{};
        sf::IntRect body_texture_chunk{};
        sf::IntRect top_texture_chunk{};
        sf::Texture* pTexture{};
        sf::Texture* pTextureTop{};
        sf::RectangleShape body{};
        sf::RectangleShape top{};

        Ground();

        Ground(sf::Texture &groundTextureRef, sf::Texture &topGroundTextureRef, const sf::RectangleShape &backgroundShape);

        void loop(const tools::Camera &camera);
    };

    class Background {
    public:
        sf::Vector2u size{};
        sf::IntRect texture_chunk{};
        sf::Texture* pTexture{};
        sf::RectangleShape shape{};
        Ground floor{};

        Background();

        explicit Background(sf::Texture &backgroundTextureRef, sf::Texture &groundTextureRef, sf::Texture &topGroundTextureRef,
                            const sf::Vector2u &size);
        void loop(const tools::Camera &camera);
    };
}

#endif //BONK_GAME_BACKGROUND_HPP