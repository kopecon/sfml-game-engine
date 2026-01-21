#include "../../../../Includes/Game/Game.hpp"
#include "../../../../Includes/Game/Engines/Render/Render.hpp"
#include "../../../../Includes/Entity/Entity.hpp"
#include "../../../../Includes/Entity/Player/States/StateSet.hpp"
#include "../../../../Includes/Game/Engines/AnimationEngine/Animatable.hpp"


Render::Render(entity::Entity &entity) :
    entity_(entity),
    root_(
        std::make_unique<Composite>(
            static_cast<std::string>(entity_.getName()) + "render_root")
        )
    {}

void Render::setRoot(std::unique_ptr<Composite> composite) {
    root_ = std::move(composite);
}

Composite & Render::getRoot() const {
    return *root_;
}

void Render::loop() const {
    // This could be improved, but I don't care anymore... it works well enough now.
    const Camera &camera = entity_.game.video.camera;

    const auto cameraCenter = camera.view.getCenter();
    const auto cameraWidth = camera.view.getSize().x / camera.zoom;

    const auto cameraRBorder = cameraCenter.x + cameraWidth / 2.f;
    const auto cameraLBorder = cameraCenter.x - cameraWidth / 2.f;

    const auto renderRBorder = entity_.position.x + entity_.render.getRoot().getGlobalBounds().size.x / 2.f;
    const auto renderLBorder = entity_.position.x - entity_.render.getRoot().getGlobalBounds().size.x / 2.f;

    if (cameraRBorder > renderRBorder || cameraLBorder < renderLBorder) {
        entity_.position = {
            cameraCenter.x,
            entity_.position.y};
    }
}

void Render::update() const {
    if (auto* anim = dynamic_cast<AnimationEngine<player::StateSet>*>(root_.get())) {
        anim->update(entity_.game.time.get());
    }
    root_->setPosition(entity_.position);
}
