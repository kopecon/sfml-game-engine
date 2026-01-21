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

        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::IDLE,         2, true ));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::WINKING,      2, true ));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::WALKING,      4, true ));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::RUNNING,      8, true ));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::CROUCHING,    6, true ));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::JUMPING,      8, false));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::DYING,        8, false));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::DISAPPEARING, 4, false));
        aComposite->addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::ATTACKING,    8, false));

        auto *c = aComposite.get();
        aComposite->setSelectionStrategy([c, &player] {
            c->setAnimation(player.getState().getID());
        });
        aComposite->getSprite()->setScale(hd::divide(player.getCharacterSize(), aComposite->getGlobalBounds().size));
        
        player.render.setRoot(std::move(aComposite));
        player.render.getRoot().setOrigin(player.render.getRoot().getCenter());
        player.render.getRoot().showOutline(sf::Color::Blue);
    }
} // player