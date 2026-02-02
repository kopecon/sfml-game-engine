//
// Created by Andrew on 20/01/2026.
//

#ifndef BONK_GAME_ANIMATABLE_HPP
#define BONK_GAME_ANIMATABLE_HPP


class Animatable {
public:
    virtual ~Animatable() = default;
    virtual void animate(float dt) = 0;
};


#endif //BONK_GAME_ANIMATABLE_HPP