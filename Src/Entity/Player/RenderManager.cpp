//
// Created by Andrew on 02/01/2026.
//

#include "../../../Includes/Entity/Player/RenderManager.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/PlayerSprite.hpp"
#include "../../../Includes/Game/Engines/SceneGraph/RectangleShape.hpp"
#include "../../../Includes/World/World.hpp"


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