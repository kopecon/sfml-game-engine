//
// Created by Andrew on 14/11/2025.
//

#ifndef BONK_GAME_CAMERA_HPP
#define BONK_GAME_CAMERA_HPP

#include <SFML/Graphics.hpp>

namespace entity {
    class Entity;
}


class Camera {
public:
    Camera();
    explicit Camera(sf::Window &window);

    sf::Window *pWindow{nullptr};
    sf::View view{};
    entity::Entity *pTarget{nullptr};

    void followTarget();
};

#endif //BONK_GAME_CAMERA_HPP