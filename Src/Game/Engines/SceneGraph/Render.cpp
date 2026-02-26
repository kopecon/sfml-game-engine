#include "Game/Engines/SceneGraph/Render.hpp"
#include "Game/Game.hpp"


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

    const auto renderRBorder = entity_.physics().properties().position.x + getGlobalBounds().size.x / 2.f;
    const auto renderLBorder = entity_.physics().properties().position.x - getGlobalBounds().size.x / 2.f;

    if (cameraRBorder > renderRBorder || cameraLBorder < renderLBorder) {
        entity_.physics().properties().position = {
            cameraCenter.x,
            entity_.physics().properties().position.y};
    }
}


void Render::update() {
    play(entity_.game.getTime().dt());
    setPosition(entity_.physics().properties().position);
}

void Render::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const {}
