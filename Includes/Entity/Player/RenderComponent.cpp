//
// Created by Andrew on 29/12/2025.
//

#include "RenderComponent.hpp"
#include "Player.hpp"


namespace player {
    RenderComponent::RenderComponent(Player &player):
        player(player) {}

    void RenderComponent::initShapeSize() {
        shape.setSize(static_cast<sf::Vector2f>(player.pTexture->getSize()));
    }
} // player