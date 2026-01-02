//
// Created by Andrew on 02/01/2026.
//

#include "RenderManager.hpp"
#include "Player.hpp"


namespace player {
    RenderManager::RenderManager(Player &player): player(player) {
        const auto &texture = player.game.textures.player;

        auto playerShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(texture.getSize()));

        playerShape->setTexture(&texture);
        playerShape->setTextureRect(sf::IntRect({0, 0}, {32, 32}));
        playerShape->setOrigin(playerShape->getGeometricCenter());

        auto composite = std::make_unique<entity::ShapeComposite>();
        composite->addShape(std::move(playerShape));

        player.render.addComposite(std::move(composite));
    }
} // player