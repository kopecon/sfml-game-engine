//
// Created by Andrew on 18/01/2026.
//

#ifndef BONK_GAME_ANIMATION_HPP
#define BONK_GAME_ANIMATION_HPP
#include <functional>
#include "SFML/System/Vector2.hpp"


template<typename AnimationEnum>
requires (std::is_enum_v<AnimationEnum>)
class Animation {
public:
    enum class State {
        READY, PLAYING, END, COMPLETED
    };
#pragma region constructors
    Animation() = default;

    Animation(const AnimationEnum &id, const int &framesPerRow, const bool &looping=true) :
    ID(id),
    framesPerRow(framesPerRow),
    fps(static_cast<float>(framesPerRow)),
    spf(1.f/fps),
    looping(looping)
    {}

#pragma endregion
    AnimationEnum ID{0};  // Represents row index starting from 0;
    sf::Vector2i frameIndex = {0, static_cast<int>(ID)};
    sf::Vector2i *pIndex = &frameIndex;
    int framesPerRow{};
    float timer{0.0f};  // tracks elapsed time
    float fps{};  // frames per second
    float spf{};  // seconds per frame
    bool started{false};
    bool finished{false};
    bool looping{true};
    State state{State::READY};

    bool operator!=(const Animation &other) const {
        return this->ID != other.ID;
    };

    bool operator==(const Animation &other) const {
        return this->ID == other.ID;
    };

    struct Hash {
        size_t operator()(const Animation& anim) const noexcept {
            return std::hash<AnimationEnum>()(anim.ID);
        }
    };
};


#endif //BONK_GAME_ANIMATION_HPP