//
// Created by Andrew on 14/11/2025.
//

#include "../../Includes/Game/Camera.hpp"
#include "../../Includes/Entity/Entity.hpp"


Camera::Camera() = default;

Camera::Camera(const sf::Window &window) {
    view.setCenter({0, 0});
    view.setSize(static_cast<sf::Vector2f>(window.getSize()));
    view.zoom(zoom);
}

void Camera::followTarget() {
    if (pTarget) { //TODO: MANAGE DELETION OF TARGET
        view.setCenter({
            pTarget->position + targetFollowOffset
        });
    }
}