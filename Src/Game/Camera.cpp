//
// Created by Andrew on 14/11/2025.
//

#include "../../Includes/Game/Camera.hpp"


Camera::Camera() = default;

Camera::Camera(sf::Window &window): pWindow(&window) {
    view.setCenter({0, 0});
    view.setSize(static_cast<sf::Vector2f>(window.getSize()));
    view.zoom(1);
}

void Camera::followTarget() {
    view.setCenter({pTarget->pShape->getPosition().x, pTarget->pShape->getPosition().y-pTarget->pShape->getGlobalBounds().size.y-50.f});
}
