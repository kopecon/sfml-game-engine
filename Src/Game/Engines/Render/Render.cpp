#include "../../../../Includes/Game/Game.hpp"
#include "../../../../Includes/Game/Engines/Render/Render.hpp"

#include <iostream>

#include "../../../../Includes/Entity/Entity.hpp"


Render::Render(entity::Entity &entity) :
    Composite(entity.getName().data()),
    entity(entity) {
}

void Render::loop() const {
    // This could be improved, but I don't care anymore... it works well enough now.
    const Camera &camera = entity.game.video.camera;

    const auto cameraCenter = camera.view.getCenter();
    const auto cameraWidth = camera.view.getSize().x / camera.zoom;

    const auto cameraRBorder = cameraCenter.x + cameraWidth / 2.f;
    const auto cameraLBorder = cameraCenter.x - cameraWidth / 2.f;

    const auto renderRBorder = entity.position.x + entity.render.getGlobalBounds().size.x / 2.f;
    const auto renderLBorder = entity.position.x - entity.render.getGlobalBounds().size.x / 2.f;

    if (cameraRBorder > renderRBorder || cameraLBorder < renderLBorder) {
        entity.position = {
            cameraCenter.x,
            entity.position.y};
    }
}

void Render::update() {
    setPosition(entity.position);
}
