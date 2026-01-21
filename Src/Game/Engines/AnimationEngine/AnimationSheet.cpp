//
// Created by Andrew on 18/01/2026.
//

#include "../../../../Includes/Game/Engines/AnimationEngine/AnimationSheet.hpp"

AnimationSheet::AnimationSheet(const sf::Texture &texture, const sf::Vector2u &frameSize):
    texture(texture),
    frameSize(frameSize),
    rows(texture.getSize().y/frameSize.y),
    columns(texture.getSize().x/frameSize.x) {}

AnimationSheet::AnimationSheet(const sf::Texture &texture, const unsigned &rows, const unsigned &columns):
    texture(texture),
    frameSize(sf::Vector2u(
        texture.getSize().x / columns,
        texture.getSize().y / rows
    )),
    rows(rows),
    columns(columns) {}
