#ifndef BONK_GAME_CAMERA_HPP
#define BONK_GAME_CAMERA_HPP

#include <SFML/Graphics.hpp>

namespace entity {
    class Entity;
}


class Camera {
public:
    explicit Camera(sf::RenderTexture &renderTexture);

    entity::Entity *pTarget{nullptr};
    sf::View view{};
    float zoom{1.f};

    void update();

private:
    sf::RenderTexture &renderTexture_;
    sf::Vector2f targetFollowOffset_{0.f, -64.f}; // TODO: Manage magic number
    void followTarget();
};

#endif //BONK_GAME_CAMERA_HPP