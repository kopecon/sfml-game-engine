//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATION_ENGINE_HPP
#define BONK_GAME_ANIMATION_ENGINE_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>


struct AnimationSheet {
    sf::Texture *pTexture{};
    sf::Vector2i frameSize{};
    [[nodiscard]] sf::Vector2i getFrameSize(const int &framesPerRow, const int &framesPerColumn) const;
};

template<typename States>
class AnimationEntry {
public:
    enum AnimationState {
        READY, PLAYING, END, COMPLETED
    };
#pragma region constructors
    AnimationEntry() = default;

    AnimationEntry(const States &id, const int &framesPerRow, const bool &looping=true) :
    id(id),
    framesPerRow(framesPerRow),
    fps(static_cast<float>(framesPerRow)),
    spf(1.f/fps),
    looping(looping)
    {}

#pragma endregion
    States id{0};  // Represents row index starting from 0;
    sf::Vector2i frameIndex = {0, static_cast<int>(id)};
    sf::Vector2i *pIndex = &frameIndex;
    int framesPerRow{};
    float timer{0.0f};  // tracks elapsed time
    float fps{};  // frames per second
    float spf{};  // seconds per frame
    bool started{false};
    bool finished{false};
    bool looping{true};
    AnimationState state{READY};

    bool operator!=(const AnimationEntry &other) const {
        return this->id != other.id;
    };

    bool operator==(const AnimationEntry &other) const {
        return this->id == other.id;
    };

    struct Hash {
        size_t operator()(const AnimationEntry& anim) const noexcept {
            return std::hash<States>()(anim.id);
        }
    };
};


template<typename States>
class AnimationEngine {
public:
#pragma region constructors
    virtual ~AnimationEngine() = default;
    AnimationEngine() = default;
    explicit AnimationEngine(const AnimationSheet &animationSheet, sf::Shape &target) :
    animationSheet(animationSheet),
    target(&target) {}
#pragma endregion

    AnimationSheet animationSheet{};
    AnimationEntry<States> *pPreviousAnimation{nullptr};
    AnimationEntry<States> *pCurrentAnimation{nullptr};
    std::unordered_map<States, AnimationEntry<States>> animationSet;
    sf::Shape *target{};

    [[nodiscard]] sf::IntRect currentFrame() const {
        auto frameCoord = sf::Vector2i(
            pCurrentAnimation->frameIndex.x*animationSheet.frameSize.x,
            pCurrentAnimation->frameIndex.y*animationSheet.frameSize.y
        );
        return {frameCoord, animationSheet.frameSize};
    }
    void set(const States &animationID) {
        auto *pNewAnimation = &animationSet[animationID];
        if (pCurrentAnimation == nullptr) {
            pCurrentAnimation = pNewAnimation;
        }
        else if (pCurrentAnimation != pNewAnimation) {
            // Stash previous animation
            pPreviousAnimation = pCurrentAnimation;
            // Load desired animation
            pCurrentAnimation = pNewAnimation;
            // Reset the animation
            pCurrentAnimation->frameIndex.x = 0;
            pCurrentAnimation->state = AnimationEntry<States>::READY;
        }
    }

    void add(const AnimationEntry<States> &animation) {
        animationSet.emplace(animation.id, animation);

        if (pCurrentAnimation == nullptr) {
            set(animation.id);
        }
    }

    void onEnd(const States &animationID, const std::function<void()> &function) {
        if (animationSet[animationID].state == AnimationEntry<States>::END) {
            function();
        }
    }

    bool completed(const States &animationID) {
        if (animationSet[animationID].state == AnimationEntry<States>::COMPLETED) {
            return true;
        }
        return false;
    }

    virtual void update(const float &dt) const {
        if (pCurrentAnimation->state == AnimationEntry<States>::END) {
            pCurrentAnimation->state = AnimationEntry<States>::COMPLETED;
            return;
        }
        target->setTextureRect(currentFrame());
        pCurrentAnimation->state = AnimationEntry<States>::PLAYING;
        pCurrentAnimation->timer += dt;
        // When it is the time to move to the next frame
        if (pCurrentAnimation->timer >= pCurrentAnimation->spf) {
            pCurrentAnimation->frameIndex.x += 1;
            pCurrentAnimation->timer = 0.f;  // Reset timer
        }
        // Evaluate the end of animationManager
        if (pCurrentAnimation->frameIndex.x+1 > pCurrentAnimation->framesPerRow) {
            // LOOP
            if (pCurrentAnimation->looping) pCurrentAnimation->frameIndex.x = 0;
            // DONT LOOP
            else {
                pCurrentAnimation->state = AnimationEntry<States>::END;
                pCurrentAnimation->frameIndex.x = pCurrentAnimation->framesPerRow-1;
            }
        }
    }
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP