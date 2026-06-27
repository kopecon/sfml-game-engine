#include "Video/Camera.hpp"

#include "Engine.hpp"
#include "EntityManager/Entity/Entity.hpp"
#include "Video/VideoComponent.hpp"


Camera::Camera(Engine &engine) : engine_(engine), renderTexture_(engine.getVideo().renderTexture()) {
    view.setSize(static_cast<sf::Vector2f>(VideoComponent::GAME_RESOLUTION));
    view.setCenter(static_cast<sf::Vector2f>(VideoComponent::BASE_CENTER));
    view.zoom(zoom);
}

void Camera::update() {
    followTarget();
    renderTexture_.setView(view);
}

void Camera::setTarget(const std::weak_ptr<entity::Body> &target) {
    pTarget = &target;
}

void Camera::followTarget() {
    if (!pTarget) return;

    if (const auto &target = pTarget->lock()) {
        view.setCenter({
            target->position() + targetFollowOffset_
        });
    }
}
