//
// Created by Andrew on 14/11/2025.
//

#include "../Includes/Camera.hpp"

#include <iostream>


Camera::Camera() = default;

Camera::Camera(sf::Window &window): pWindow(&window) {
    view.setCenter(static_cast<sf::Vector2f>(window.getSize())/2.f);
    view.setSize(static_cast<sf::Vector2f>(window.getSize()));
    view.zoom(0.75);
}

void Camera::followTarget() {
    view.setCenter({pTarget->pShape->getPosition().x, pTarget->pShape->getPosition().y-static_cast<float>(pWindow->getSize().y)/5.f});
}
