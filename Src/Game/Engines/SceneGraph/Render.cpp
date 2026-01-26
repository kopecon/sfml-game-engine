#include "../../../../Includes/Game/Engines/SceneGraph/Render.hpp"
#include "../../../../Includes/Game/Engines/SceneGraph/Composite.hpp"
#include "../../../../Includes/Game/Game.hpp"
#include "../../../../Includes/Entity/Entity.hpp"


Render::Render(entity::Entity &entity) :
    entity_(entity)
    {rename(static_cast<std::string>(entity.getName()) + " render");}

void Render::loop() const {
    // This could be improved, but I don't care anymore... it works well enough now.
    const Camera &camera = entity_.game.getVideo().getCamera();

    const auto cameraCenter = camera.view.getCenter();
    const auto cameraWidth = camera.view.getSize().x / camera.zoom;

    const auto cameraRBorder = cameraCenter.x + cameraWidth / 2.f;
    const auto cameraLBorder = cameraCenter.x - cameraWidth / 2.f;

    const auto renderRBorder = entity_.position.x + entity_.render.getGlobalBounds().size.x / 2.f;
    const auto renderLBorder = entity_.position.x - entity_.render.getGlobalBounds().size.x / 2.f;

    if (cameraRBorder > renderRBorder || cameraLBorder < renderLBorder) {
        entity_.position = {
            cameraCenter.x,
            entity_.position.y};
    }
}


void Render::update() {
    play(entity_.game.getTime().get());
    setPosition(entity_.position);
}
