#pragma once

#include "Video/SceneGraph/Composite.hpp"


namespace entity {
    class Entity;

    class RenderComponent final : public render::Composite, public id::Node<RenderComponent> {
    public:
        explicit RenderComponent(const Entity &entity);

        // void loop() const noexcept;

        void update() noexcept;

    private:
        const Entity &entity_;

        void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const noexcept override;
    };
} // entity
