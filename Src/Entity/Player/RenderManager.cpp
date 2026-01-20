//
// Created by Andrew on 02/01/2026.
//

#include "../../../Includes/Entity/Player/RenderManager.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Game/Engines/Render/AnimatedComposite.hpp"
#include "../../../Includes/World/World.hpp"


namespace player {
    RenderManager::RenderManager(Player &player) : player(player) {
        auto &texture = player.game.textures.player;
        auto animationSheet = std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));

        auto aComposite = std::make_unique<AnimatedComposite<StateSet>>(std::move(animationSheet));

        aComposite->setScale(hd::divide(player.getCharacterSize(), aComposite->getGlobalBounds().size));

        player.render.setRoot(std::move(aComposite));
        player.render.getRoot().setOrigin(player.render.getRoot().getCenter());
        player.render.getRoot().showOutline(sf::Color::Blue);
    }
} // player