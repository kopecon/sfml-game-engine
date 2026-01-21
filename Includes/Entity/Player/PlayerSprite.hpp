//
// Created by Andrew on 21/01/2026.
//

#ifndef BONK_GAME_PLAYER_SPRITE_HPP
#define BONK_GAME_PLAYER_SPRITE_HPP
#include "../../Game/Engines/Render/AnimatedComposite.hpp"
#include "States/StateSet.hpp"


namespace player {
    class Player;


    class PlayerSprite final : public AnimatedComposite<StateSet>{
        Player &player;
        void selectAnimation() override;

    public:
        PlayerSprite(Player &player, std::unique_ptr<AnimationSheet> animationSheet);
    };
} // player

#endif //BONK_GAME_PLAYER_SPRITE_HPP