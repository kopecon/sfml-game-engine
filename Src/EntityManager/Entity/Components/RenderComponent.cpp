#include "EntityManager/Entity/Components/RenderComponent.hpp"

#include "Engine.hpp"

namespace entity {
    RenderComponent::RenderComponent(const Entity &entity) : entity_(entity) {
    }

    // void RenderComponent::loop() const noexcept {
    //     // This could be improved, but I don't care anymore... it works well enough now.
    //     const Camera &camera = entity_.engine.getVideo().getCamera();
    //
    //     const auto cameraCenter = camera.view.getCenter();
    //     const auto cameraWidth = camera.view.getSize().x / camera.zoom;
    //
    //     const auto cameraRBorder = cameraCenter.x + cameraWidth / 2.f;
    //     const auto cameraLBorder = cameraCenter.x - cameraWidth / 2.f;
    //
    //     const auto renderRBorder = entity_.position().x + getGlobalBounds().size.x / 2.f;
    //     const auto renderLBorder = entity_.position().x - getGlobalBounds().size.x / 2.f;
    //
    //     if (cameraRBorder > renderRBorder || cameraLBorder < renderLBorder) {
    //         entity_.position() = {
    //             cameraCenter.x,
    //             entity_.position().y
    //         };
    //     }
    // }


    void RenderComponent::update() noexcept {
        play(entity_.engine.time().dt());
        setPosition(entity_.position());
    }

    void RenderComponent::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const noexcept {
    }
} // entity
