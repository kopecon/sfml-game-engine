//
// Created by Andrew on 02/01/2026.
//

#include "Game/Game.hpp"
#include "Game/Engines/SceneGraph/RectangleShape.hpp"
#include "Game/World/World.hpp"
#include "Game/World/Entity/Player/Components/Render/RenderManager.hpp"
#include "Game/World/Entity/Player/Components/Render/PlayerSprite.hpp"
#include "Game/World/Entity/Player/Player.hpp"


namespace player {
    RenderManager::RenderManager(Player &player) : player_(player) {
        // PLAYER SPRITE
        auto &texture = player.game.getTextures().player;
        auto animationSheet = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));
        auto playerSprite = std::make_unique<PlayerSprite>(player, std::move(animationSheet));
        playerSprite->rename("PlayerSprite");
        playerSprite->getSprite().setScale(hd::divide(player.getCharacterSize(), playerSprite->getGlobalBounds().size));


        // RENDER
        auto &render = player.render;
        render.add(std::move(playerSprite));
        render.setOrigin({render.getCenter().x, render.getCenter().y + 0.5f * render.getGlobalBounds().size.y});
        // render.showOutline(sf::Color::Blue);
    }
} // player