#include "Game/Engines/SceneGraph/ParallaxLayer.hpp"
#include "Game/Components/Video/Camera.hpp"
#include "Utils/utils.hpp"


ParallaxLayer::ParallaxLayer(const sf::Texture &tex, const Camera &camera, const float scrollSpeed)
    : Sprite(tex),
      camera_(camera),
      referencePoint(camera.view.getCenter()),
      scrollSpeed_(scrollSpeed) {
    setOrigin(getCenter());
}

void ParallaxLayer::update() {
    const auto cameraCenter = camera_.view.getCenter();
    const auto viewSize = camera_.view.getSize();
    const auto scale = getScale();

    // Calculate movement relative to the anchor
    const sf::Vector2f delta = cameraCenter - referencePoint;

    const sf::Vector2i rectSize{hd::divide(viewSize, scale)};

    const sf::Vector2i rectPos{hd::divide(delta * scrollSpeed_, scale) - static_cast<sf::Vector2f>(rectSize) / 2.f};

    getSprite().setTextureRect(sf::IntRect(rectPos, rectSize));

    // Keep the container locked to the camera
    setPosition(cameraCenter);
}
