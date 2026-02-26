#ifndef BONK_GAME_CAMERA_HPP
#define BONK_GAME_CAMERA_HPP

#include <SFML/Graphics.hpp>

namespace entity {
    class Entity;
}


class Camera {
public:
    Camera();
    explicit Camera(const sf::Window &window);

    sf::View view{};
    float zoom{0.8f};
    entity::Entity *pTarget{nullptr};
    sf::Vector2f targetFollowOffset{0.f, -140.f}; // Fixed value is just temporary

    void followTarget();
};

#endif //BONK_GAME_CAMERA_HPP