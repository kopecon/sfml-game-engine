# pragma once

#include <SFML/Graphics.hpp>

class Engine;
class VideoComponent;

namespace entity {
    class Body;
    class Entity;
}


class Camera {
public:
    explicit Camera(Engine &engine);

    sf::View view{};
    float zoom{1.f};

    void update();

    void setTarget(const std::weak_ptr<entity::Body> &target);

private:
    Engine &engine_;
    const std::weak_ptr<entity::Body> *pTarget{};
    sf::RenderTexture &renderTexture_;
    sf::Vector2f targetFollowOffset_{0.f, -64.f}; // TODO: Manage magic number
    void followTarget();
};
