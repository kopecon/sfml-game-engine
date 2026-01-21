//
// Created by Andrew on 02/01/2026.
//

#include "../../../Includes/Entity/Player/RenderManager.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/PlayerSprite.hpp"
#include "../../../Includes/Game/Engines/Render/AnimatedComposite.hpp"
#include "../../../Includes/World/World.hpp"


namespace player {
    RenderManager::RenderManager(Player &player) : player(player) {
        // PLAYER SPRITE
        auto &texture = player.game.textures.player;
        auto animationSheet = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));
        auto animationSheet1 = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));
        auto animationSheet2 = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));
        auto animationSheet3 = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));
        auto animationSheet4 = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));

        auto playerSprite = std::make_unique<PlayerSprite>(player, std::move(animationSheet));

        playerSprite->getSprite().setScale(hd::divide(player.getCharacterSize(), playerSprite->getGlobalBounds().size));
        // TEST SPRITE
        auto testSprite1 = std::make_unique<PlayerSprite>(player, std::move(animationSheet1));
        auto testSprite2 = std::make_unique<PlayerSprite>(player, std::move(animationSheet2));
        auto testSprite3 = std::make_unique<PlayerSprite>(player, std::move(animationSheet3));
        auto testSprite4 = std::make_unique<PlayerSprite>(player, std::move(animationSheet4));
        float distance = 100;
        testSprite1->move({-distance, -distance});
        testSprite2->move({distance, -distance});
        testSprite3->move({-distance, distance});
        testSprite4->move({distance, distance});

        playerSprite->add(std::move(testSprite1));
        playerSprite->add(std::move(testSprite2));
        playerSprite->add(std::move(testSprite3));
        playerSprite->add(std::move(testSprite4));
        playerSprite->showOutline();

        // RENDER
        player.render.changeRoot(std::move(playerSprite));
        auto &root = player.render.getRoot();
        root.setOrigin(player.render.getRoot().getCenter());
        // root.showOutline(sf::Color::Blue);
    }
} // player