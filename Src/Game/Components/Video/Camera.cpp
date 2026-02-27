#include "Game/Components/Video/Camera.hpp"

#include "Game/Components/Video/VideoComponent.hpp"
#include "Game/World/Entity/Entity.hpp"


Camera::Camera(sf::RenderTexture &renderTexture)
    : renderTexture_(renderTexture) {
    view.setSize(static_cast<sf::Vector2f>(VideoComponent::GAME_RESOLUTION));
    view.setCenter(static_cast<sf::Vector2f>(VideoComponent::BASE_CENTER));
    view.zoom(zoom);
}

void Camera::update() {
    followTarget();
    renderTexture_.setView(view);
}

void Camera::followTarget() {
    if (pTarget) {
        //TODO: MANAGE DELETION OF TARGET
        view.setCenter({
            pTarget->physics().properties().position + targetFollowOffset_
        });
    }
}
