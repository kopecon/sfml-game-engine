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
        player.render.animator.setTarget(*player.render.getSprite());
        player.render.animator.setAnimationSheet(std::make_unique<AnimationSheet>(
            texture,
            sf::Vector2u(32, 32)
            ));
        player.render.animator.add(
            std::make_unique<Animation>(0, 2, true)
        );
        player.render.animator.add(
            std::make_unique<Animation>(1, 2, true)
        );
        std::cout << player.render.animator.getCurrentAnimation()->getID() << "\n";
        player.render.setOrigin(player.render.getCenter());
        player.render.showOutline(sf::Color::Blue);
    }
} // player