//
// Created by Andrew on 02/01/2026.
//

#include "../../../Includes/Entity/Player/RenderManager.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/PlayerSprite.hpp"
#include "../../../Includes/Game/Engines/SceneGraph/AnimatedSprite.hpp"
#include "../../../Includes/World/World.hpp"


namespace player {
    RenderManager::RenderManager(Player &player) : player(player) {
        // PLAYER SPRITE
        auto &texture = player.game.textures.player;
        auto animationSheet = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));
        auto animationSheet1 = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));

        auto playerSprite = std::make_unique<PlayerSprite>(player, std::move(animationSheet));

        playerSprite->setScale(hd::divide(player.getCharacterSize(), playerSprite->getGlobalBounds().size));
        playerSprite->rename("PlayerSprite");
        // TEST
        auto testSprite1 = std::make_unique<PlayerSprite>(player, std::move(animationSheet1));
        testSprite1->rename("testSprite1");
        testSprite1->move({20.f, 0.f});
        playerSprite->add(std::move(testSprite1));
        // RENDER
        auto &render = player.render;
        render.add(std::move(playerSprite));
        // render.add(std::move(testSprite1));
        render.setOrigin({render.getCenter().x, render.getGlobalBounds().size.y});
        render.showOutline(sf::Color::Blue);
    }
} // player