//
// Created by Andrew on 14/11/2025.
//

#ifndef BONK_GAME_CAMERA_HPP
#define BONK_GAME_CAMERA_HPP

#include <SFML/Graphics.hpp>


namespace tools {
    class Camera {
    public:
        explicit Camera(const sf::Window &window);
        const sf::Window &window{};
        sf::View view{};

        void follow_point(const sf::Vector2f &point);
    };
} // tools

#endif //BONK_GAME_CAMERA_HPP