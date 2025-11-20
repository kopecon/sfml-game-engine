//
// Created by Andrew on 14/11/2025.
//

#include "../Includes/Camera.hpp"

namespace tools {
    Camera::Camera(const sf::Window &window): window(window) {
        view.setCenter(static_cast<sf::Vector2f>(window.getSize())/2.f);
        view.setSize(static_cast<sf::Vector2f>(window.getSize()));
        view.zoom(0.75);
    }

    void Camera::follow_point(const sf::Vector2f &point) {
        view.setCenter({point.x, point.y-200});
    }
} // tools