#pragma once

#include <SFML/Graphics/Texture.hpp>


class Animatable {
public:
    virtual ~Animatable() = default;

    virtual void animate(float dt) noexcept = 0;

    virtual void setTextureRect(const sf::IntRect &rect) noexcept = 0;
};
