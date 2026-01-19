//
// Created by Andrew on 18/01/2026.
//

#ifndef BONK_GAME_ANIMATION_HPP
#define BONK_GAME_ANIMATION_HPP
#include <functional>
#include "SFML/System/Vector2.hpp"
#include "../../../../Utils/EnumSet.hpp"

template<EnumSetConcept AnimationSet>
class Animation {
    AnimationSet::ID id_{0};  // Represents row index starting from 0;
    unsigned frame_ = 0;
    float timer_{0.0f};  // tracks elapsed time
    unsigned fpr_{};  // frames per row
    float    fps_{};  // frames per second  (by default is equal to fpr: "it takes one second to play every frame")
    float    spf_{};  // seconds per frame

public:
    enum class Status {
        READY, PLAYING, END, COMPLETED
    };

#pragma region constructors
    Animation() = default;

    Animation(const typename AnimationSet::ID &id, const int &fpr, const bool &looping=true) :
    id_(id),
    fpr_(fpr),
    fps_(static_cast<float>(fpr)),
    spf_(1.f/fps_),
    looping(looping)
    {}
#pragma endregion

#pragma region operators
    bool operator!=(const Animation &other) const {
        return this->id_ != other.id_;
    };

    bool operator==(const Animation &other) const {
        return this->id_ == other.id_;
    };

    struct Hash {
        size_t operator()(const Animation& anim) const noexcept {
            return std::hash<typename AnimationSet::ID>()(anim.id_);
        }
    };
#pragma endregion

    bool started{false};
    bool finished{false};
    bool looping{true};
    Status status{Status::READY};

    void setFPS(const float &value) {
        fps_ = value;
        spf_ = 1 / fps_;
    }

    void setSPF(const float &value) {
        spf_ = value;
        fps_ = 1 / spf_;
    }

    [[nodiscard]] typename AnimationSet::ID getID() const {
        return id_;
    }

    [[nodiscard]] unsigned getFPR() const {
        return fpr_;
    }

    [[nodiscard]] float getFPS() const {
        return fps_;
    }

    [[nodiscard]] float getSPF() const {
        return spf_;
    }

    [[nodiscard]] sf::Vector2u getFrameIndex() {
        return {frame_, static_cast<unsigned>(id_)};
    }

    void reset() {
        status = Status::READY;
        frame_ = 0;
    }

    void update(const float &dt) {
        if (status == Status::END) {
            status = Status::COMPLETED;
            return;
        }
        status = Status::PLAYING;
        timer_ += dt;
        // When it is the time to move to the next frame
        if (timer_ >= spf_) {
            frame_ += 1;
            timer_ = 0.f;  // Reset timer
        }
        // Evaluate the end of animationManager
        if (frame_+1 > fpr_) {
            // LOOP
            if (looping) frame_ = 0;
            // DONT LOOP
            else {
                status = Status::END;
                frame_ = fpr_-1;
            }
        }
    };
};

#endif //BONK_GAME_ANIMATION_HPP