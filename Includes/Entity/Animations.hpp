//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATIONS_HPP
#define BONK_GAME_ANIMATIONS_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Player/States/State.hpp"


struct AnimationSheet {
    sf::Texture *pTexture{};
    sf::Vector2i frameSize{};
    [[nodiscard]] sf::Vector2i getFrameSize(const int &framesPerRow, const int &framesPerColumn) const;
};

class AnimationEntry {
public:
    enum AnimationState {
        READY, PLAYING, END, COMPLETED
    };
#pragma region constructors
    AnimationEntry();
    AnimationEntry(const StateManager::States &id, const int &framesPerRow, const bool &looping=true);

    AnimationEntry(const StateManager::States &id, const int &framesPerRow, const float &fps, const bool &looping=true);

#pragma endregion
    StateManager::States id{0};  // Represents row index starting from 0;
    sf::Vector2i frameIndex = {0, static_cast<int>(id)};
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

class Animations {
public:
#pragma region constructors
    Animations();
    explicit Animations(const AnimationSheet &animationSheet, sf::Shape &target);
#pragma endregion

    AnimationSheet animationSheet{};
    AnimationEntry *pPreviousAnimation{nullptr};
    AnimationEntry *pCurrentAnimation{nullptr};
    std::unordered_map<StateManager::States, AnimationEntry> animationSet;
    sf::Shape *target{};

    [[nodiscard]] sf::IntRect currentFrame() const;

    void set(const StateManager::States &animationID);

    void add(const AnimationEntry &animation);

    void onEnd(const StateManager::States &animationID, const std::function<void()> &function);

    bool completed(const StateManager::States &animationID);

    void update(const float &dt) const;
};

#endif //BONK_GAME_ANIMATIONS_HPP