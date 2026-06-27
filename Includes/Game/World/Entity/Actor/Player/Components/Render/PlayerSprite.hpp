#ifndef BONK_GAME_PLAYER_SPRITE_HPP
#define BONK_GAME_PLAYER_SPRITE_HPP

#include "Game/Engines/SceneGraph/AnimatedSprite.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultStateSet.hpp"


namespace player {
    class Player;


    class PlayerSprite final : public AnimatedSprite<DefaultStateSet>{
    public:
        explicit PlayerSprite(Player &player);

    private:
        // REFERENCES
        Player &player_;

        static std::unique_ptr<AnimationSheet> constructAnimationSheet(const Player& player);
    };
} // player

#endif //BONK_GAME_PLAYER_SPRITE_HPP