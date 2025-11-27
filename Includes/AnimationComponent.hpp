//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATED_HPP
#define BONK_GAME_ANIMATED_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "../Includes/AnimationComponent.hpp"

struct AnimationSheet {
    sf::Texture *pTexture{};
    sf::Vector2i frameSize{};
    [[nodiscard]] sf::Vector2i getFrameSize(const int &framesPerRow, const int &framesPerColumn) const;
};

class AnimationEntry {
public:
    enum AnimationState {
        READY, PLAYING, FINISHED
    };
#pragma region constructors
    AnimationEntry();
    AnimationEntry(const int&id, const int &framesPerRow, const bool &looping=true);

    AnimationEntry(const int&id, const int &framesPerRow, const float &fps, const bool &looping=true);

#pragma endregion
    int id{0};  // Represents row index starting from 0;
    sf::Vector2i frameIndex = {0, id};
    sf::Vector2i *pIndex = &frameIndex;
    int framesPerRow{8};
    float timer{0.0f};  // tracks elapsed time
    float fps{static_cast<float>(framesPerRow)};  // frames per second
    bool started{false};
    bool finished{false};
    bool looping{true};
    AnimationState state{READY};

    bool operator!=(const AnimationEntry &other) const;

    bool operator==(const AnimationEntry &other) const;

    struct Hash {size_t operator()(const AnimationEntry& anim) const noexcept;};
};

class AnimationComponent {
public:
#pragma region constructors
    AnimationComponent();
    explicit AnimationComponent(const AnimationSheet &animationSheet, sf::Shape &target);
#pragma endregion

    AnimationSheet animationSheet{};
    AnimationEntry *pPreviousAnimation{nullptr};
    AnimationEntry *pCurrentAnimation{nullptr};
    std::unordered_map<int, AnimationEntry> animationSet;
    sf::Shape *target{};

    [[nodiscard]] sf::IntRect getFrame() const;

    void set(const int &animationID);

    void add(const AnimationEntry &animation);

    void onEnd(const int &animationID, const std::function<void()> &function);

    void update(const float &dt);
};

#endif //BONK_GAME_ANIMATED_HPP