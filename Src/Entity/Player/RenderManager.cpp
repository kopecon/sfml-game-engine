//
// Created by Andrew on 02/01/2026.
//

#include "../../../Includes/Entity/Player/RenderManager.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"


namespace player {
    RenderManager::RenderManager(Player &player): player(player) {
        auto &texture = player.game.textures.player;

        auto sprite = std::make_unique<sf::Sprite>(texture);

        sprite->setTextureRect(sf::IntRect({0, 0}, {32, 32})); //32 is defined by the texture used
        sprite->setScale(hd::divide(player.getCharacterSize(), sprite->getGlobalBounds().size));

        player.render.setSprite(std::move(sprite));
        player.render.setOrigin(player.render.getCenter());
        player.render.showOutline(sf::Color::Blue);
    }
} // player