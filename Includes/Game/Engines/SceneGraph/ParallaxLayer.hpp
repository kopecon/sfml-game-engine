#ifndef BONK_GAME_PARALLAX_LAYER_HPP
#define BONK_GAME_PARALLAX_LAYER_HPP
#include "Game/Engines/SceneGraph/Sprite.hpp"


// ParallaxLayer.hpp
class ParallaxLayer final : public Sprite {
public:
    ParallaxLayer(const sf::Texture &tex, const Camera &camera, float scrollSpeed);

    void update();

private:
    const Camera &camera_;
    const sf::Vector2f referencePoint{};
    float scrollSpeed_; // 0.1f for far clouds, 0.5f for distant hills, etc.
};


#endif //BONK_GAME_PARALLAX_LAYER_HPP
