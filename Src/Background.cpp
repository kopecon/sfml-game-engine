//
// Created by Andrew on 13/11/2025.
//

#include "../Includes/Background.hpp"
#include "../Includes/World.hpp"


Background::Background() = default;

Background::Background(sf::Texture &texture, const sf::Vector2u &windowSize) {
    shape.setSize({
            static_cast<float>(windowSize.x)*3,
            static_cast<float>(windowSize.y),
        });
    Scenery::init(shape, texture);
}
void Background::update() {
    if (looping) {
        loop();
    }
}