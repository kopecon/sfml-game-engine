//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATION_ENGINE_HPP
#define BONK_GAME_ANIMATION_ENGINE_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "../../Entity/Player/States/StateManager.hpp"


struct AnimationSheet {
    sf::Texture *pTexture{};
    sf::Vector2i frameSize{};
    [[nodiscard]] sf::Vector2i getFrameSize(const int &framesPerRow, const int &framesPerColumn) const;
};

template<typename StateSet>
class AnimationEntry {
public:
    enum AnimationState {
        READY, PLAYING, END, COMPLETED
    };
#pragma region constructors
    AnimationEntry() = default;

    AnimationEntry(const StateSet &id, const int &framesPerRow, const bool &looping=true) :
    id(id), framesPerRow(framesPerRow), fps(static_cast<float>(framesPerRow)), looping(looping) {}

    AnimationEntry(const StateSet &id, const int &framesPerRow, const float &fps, const bool &looping=true) :
    id(id), framesPerRow(framesPerRow), fps(fps), looping(looping) {}

#pragma endregion
    StateSet id{0};  // Represents row index starting from 0;
    sf::Vector2i frameIndex = {0, static_cast<int>(id)};
    sf::Vector2i *pIndex = &frameIndex;
    int framesPerRow{8};
    float timer{0.0f};  // tracks elapsed time
    float fps{static_cast<float>(framesPerRow)};  // frames per second
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
            return std::hash<player::States>()(anim.id);
        }
    };
};


template<typename StateSet>
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
    AnimationEntry<StateSet> *pPreviousAnimation{nullptr};
    AnimationEntry<StateSet> *pCurrentAnimation{nullptr};
    std::unordered_map<StateSet, AnimationEntry<StateSet>> animationSet;
    sf::Shape *target{};

    [[nodiscard]] sf::IntRect currentFrame() const {
        auto frameCoord = sf::Vector2i(
            pCurrentAnimation->frameIndex.x*animationSheet.frameSize.x,
            pCurrentAnimation->frameIndex.y*animationSheet.frameSize.y
        );
        return {frameCoord, animationSheet.frameSize};
    }
    void set(const StateSet &animationID) {
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
            pCurrentAnimation->state = AnimationEntry<StateSet>::READY;
        };
    };

    void add(const AnimationEntry<StateSet> &animation) {
        animationSet.emplace(animation.id, animation);

        if (pCurrentAnimation == nullptr) {
            set(animation.id);
        }
    }

    void onEnd(const StateSet &animationID, const std::function<void()> &function) {
        if (animationSet[animationID].state == AnimationEntry<StateSet>::END) {
            function();
        }
    }

    bool completed(const StateSet &animationID) {
        if (animationSet[animationID].state == AnimationEntry<StateSet>::COMPLETED) {
            return true;
        }
        return false;
    }

    virtual void update(const float &dt) const {
        if (pCurrentAnimation->state == AnimationEntry<StateSet>::END) {
            pCurrentAnimation->state = AnimationEntry<StateSet>::COMPLETED;
            return;
        }
        target->setTextureRect(currentFrame());
        pCurrentAnimation->state = AnimationEntry<StateSet>::PLAYING;
        pCurrentAnimation->timer += dt;
        // When it is the time to move to the next frame
        if (pCurrentAnimation->timer >= 1/pCurrentAnimation->fps) {
            pCurrentAnimation->frameIndex.x += 1;
            pCurrentAnimation->timer = 0.f;  // Reset timer
        }
        // Evaluate the end of animationManager
        if (pCurrentAnimation->frameIndex.x+1 > pCurrentAnimation->framesPerRow) {
            // LOOP
            if (pCurrentAnimation->looping) pCurrentAnimation->frameIndex.x = 0;
            // DONT LOOP
            else {
                pCurrentAnimation->state = AnimationEntry<StateSet>::END;
                pCurrentAnimation->frameIndex.x = pCurrentAnimation->framesPerRow-1;
            }
        }
    }
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP