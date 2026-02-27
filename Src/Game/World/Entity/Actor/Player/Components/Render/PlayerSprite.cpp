#include "Game/World/Entity/Actor/Player/Components/Render/PlayerSprite.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"
#include "Game/Game.hpp"


namespace player {
    PlayerSprite::PlayerSprite(Player &player)
        : AnimatedSprite(constructAnimationSheet(player)),
          player_(player) {
        rename("player sprite");
        setSize(player.stats().size);
        setOrigin(getCenter());

        using enum DefaultStateSet::ID;
        using Anim = Animation<DefaultStateSet>;

        animator_.addAnimation(std::make_unique<Anim>(IDLE, 2, true));
        animator_.addAnimation(std::make_unique<Anim>(WINKING, 2, false));
        animator_.addAnimation(std::make_unique<Anim>(WALKING, 4, true));
        animator_.addAnimation(std::make_unique<Anim>(RUNNING, 8, true));
        animator_.addAnimation(std::make_unique<Anim>(CROUCHING, 6, true));
        animator_.addAnimation(std::make_unique<Anim>(JUMPING, 8, false));
        animator_.addAnimation(std::make_unique<Anim>(DYING, 8, false));
        animator_.addAnimation(std::make_unique<Anim>(DISAPPEARING, 4, false));
        animator_.addAnimation(std::make_unique<Anim>(ATTACKING, 8, false));
    }

    std::unique_ptr<AnimationSheet> PlayerSprite::constructAnimationSheet(const Player &player) {
        auto &texture = player.game.getTextures().player;
        return std::make_unique<AnimationSheet>(texture, sf::Vector2u(32, 32));
    }
} // player
