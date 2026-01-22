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
        auto animationSheet5 = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));

        auto playerSprite = std::make_unique<PlayerSprite>(player, std::move(animationSheet));

        playerSprite->getSprite().setScale(hd::divide(player.getCharacterSize(), playerSprite->getGlobalBounds().size));
        playerSprite->rename("PlayerSprite");
        playerSprite->showOutline(sf::Color::Magenta);

        auto testRoot = std::make_unique<Composite>();
        // TEST SPRITE
        auto test1 = std::make_unique<PlayerSprite>(player, std::move(animationSheet1));
        auto test2 = std::make_unique<PlayerSprite>(player, std::move(animationSheet2));
        auto test3 = std::make_unique<PlayerSprite>(player, std::move(animationSheet3));
        auto test4 = std::make_unique<PlayerSprite>(player, std::move(animationSheet4));

        auto test5 = std::make_unique<PlayerSprite>(player, std::move(animationSheet5));
        float distance = 100;
        test1->move({-distance, -distance});
        test2->move({ distance, -distance});
        test3->move({-distance,  distance});
        test4->move({ distance,  distance});
        test5->move({ distance*2.f,  -distance*0.5f});

        test1->showOutline(sf::Color::Green);
        test2->showOutline(sf::Color::Green);
        test3->showOutline(sf::Color::Green);
        test4->showOutline(sf::Color::Green);
        test5->showOutline(sf::Color::Green);

        testRoot->add(std::move(test1));
        testRoot->add(std::move(test2));
        testRoot->add(std::move(test3));
        testRoot->add(std::move(test4));
        testRoot->showOutline();
        // RENDER
        auto &root = player.render.getRoot();
        root.add(std::move(testRoot));
        root.add(std::move(test5));
        root.add(std::move(playerSprite));
        root.setOrigin(root.getCenter());
        root.showOutline(sf::Color::Blue);
    }
} // player