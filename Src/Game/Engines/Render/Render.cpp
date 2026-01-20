#include "../../../../Includes/Game/Game.hpp"
#include "../../../../Includes/Game/Engines/Render/Render.hpp"
#include "../../../../Includes/Entity/Entity.hpp"


Render::Render(entity::Entity &entity) :
    entity_(entity),
    root(static_cast<std::string>(entity_.getName()) + "render_root")
    {}

void Render::loop() const {
    // This could be improved, but I don't care anymore... it works well enough now.
    const Camera &camera = entity_.game.video.camera;

    const auto cameraCenter = camera.view.getCenter();
    const auto cameraWidth = camera.view.getSize().x / camera.zoom;

    const auto cameraRBorder = cameraCenter.x + cameraWidth / 2.f;
    const auto cameraLBorder = cameraCenter.x - cameraWidth / 2.f;

    const auto renderRBorder = entity_.position.x + entity_.render.root.getGlobalBounds().size.x / 2.f;
    const auto renderLBorder = entity_.position.x - entity_.render.root.getGlobalBounds().size.x / 2.f;

    if (cameraRBorder > renderRBorder || cameraLBorder < renderLBorder) {
        entity_.position = {
            cameraCenter.x,
            entity_.position.y};
    }
}

void Render::update() {
    root.animate(entity_.game.time.get());
    root.setPosition(entity_.position);
}
