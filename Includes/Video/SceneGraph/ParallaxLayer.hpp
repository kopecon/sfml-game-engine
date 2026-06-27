#pragma once

#include "Video/SceneGraph/Sprite.hpp"


namespace render {
    class ParallaxLayer final : public Sprite {
    public:
        ParallaxLayer(const sf::Texture &tex, const Camera &camera, float scrollSpeed);

        void update() noexcept;

    private:
        const Camera &camera_;
        const sf::Vector2f referencePoint{};
        float scrollSpeed_; // 0.1f for far clouds, 0.5f for distant hills, etc.
    };
} // render
