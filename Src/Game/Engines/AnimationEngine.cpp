//
// Created by Andrew on 17/11/2025.
//

#include "Game/Engines/AnimationEngine.hpp"
#include "Game/World/Entity/Player/Player.hpp"


[[nodiscard]] sf::Vector2i AnimationSheet::getFrameSize(const int &framesPerRow, const int &framesPerColumn) const {
    auto x = static_cast<int>(pTexture->getSize().x / framesPerRow);
    auto y = static_cast<int>(pTexture->getSize().y / framesPerColumn);
    return {x, y};
}