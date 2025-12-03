//
// Created by Andrew on 13/11/2025.
//

#include "../../Includes/Scenery/Background.hpp"


Background::Background(const char* name) : Scenery(name){};

Background::Background(const char* name, const sf::Vector2u &windowSize, sf::Texture &texture) : Scenery(name) {
    shape.setSize({
            static_cast<float>(windowSize.x)*3,
            static_cast<float>(windowSize.y),
        });
}