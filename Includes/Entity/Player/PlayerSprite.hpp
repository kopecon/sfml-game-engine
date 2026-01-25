//
// Created by Andrew on 21/01/2026.
//

#ifndef BONK_GAME_PLAYER_SPRITE_HPP
#define BONK_GAME_PLAYER_SPRITE_HPP
#include "../../Game/Engines/SceneGraph/AnimatedSprite.hpp"
#include "States/StateSet.hpp"


namespace player {
    class Player;


    class PlayerSprite final : public AnimatedSprite<StateSet>{
    public:
        PlayerSprite(Player &player, std::unique_ptr<AnimationSheet> animationSheet);

    private:
        void selectAnimation();
        void updateFPS() const;
        void update() override;
        Player &player_;
    };
} // player

#endif //BONK_GAME_PLAYER_SPRITE_HPP