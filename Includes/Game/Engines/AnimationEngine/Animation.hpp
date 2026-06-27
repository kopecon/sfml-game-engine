#ifndef BONK_GAME_ANIMATION_HPP
#define BONK_GAME_ANIMATION_HPP

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "Utils/EnumSet.hpp"


enum class AnimationStatus {
    READY, PLAYING, FINISHED
};

template<EnumSetConcept AnimationSet>
class Animation {
    using Status = AnimationStatus;
public:
#pragma region constructors
    Animation(const typename AnimationSet::ID &id, const int &fpr, const bool &looping = true) : id_(id),
        fpr_(fpr),
        fps_(static_cast<float>(fpr)),
        spf_(1.f / fps_),
        looping_(looping) {
    }
#pragma endregion

#pragma region operators
    bool operator!=(const Animation &other) const {
        return this->id_ != other.id_;
    };

    bool operator==(const Animation &other) const {
        return this->id_ == other.id_;
    };

    struct Hash {
        size_t operator()(const Animation &anim) const noexcept {
            return std::hash<typename AnimationSet::ID>()(anim.id_);
        }
    };
#pragma endregion

    void setFPS(const float &value) {
        fps_ = value;
        spf_ = 1 / fps_;
    }

    void setSPF(const float &value) {
        spf_ = value;
        fps_ = 1 / spf_;
    }

    void reset() {
        status_ = Status::READY;
        frameIndex_.x = 0;
    }

    // GETTERS
    [[nodiscard]] const sf::Vector2u &getFrame() const { return frameIndex_; }
    [[nodiscard]] typename AnimationSet::ID getID() const { return id_; }
    [[nodiscard]] unsigned getFPR() const { return fpr_; }
    [[nodiscard]] float getFPS() const { return fps_; }
    [[nodiscard]] float getSPF() const { return spf_; }
    [[nodiscard]] const AnimationStatus &getStatus() const { return status_; }

    // UPDATE
    void play(const float dt) {
        if (status_ == Status::FINISHED) {
            return;
        }
        status_ = Status::PLAYING;
        timer_ += dt;
        // When it is the time to move to the next frame
        if (timer_ >= spf_) {
            frameIndex_.x += 1;
            timer_ = 0.f; // Reset timer
        }
        // Evaluate the end of animationManager
        if (frameIndex_.x + 1 > fpr_) {
            // LOOP
            if (looping_) frameIndex_.x = 0;
            // DONT LOOP
            else {
                status_ = Status::FINISHED;
                frameIndex_.x = fpr_ - 1;
            }
        }
    }

private:
    typename AnimationSet::ID id_{0};
    sf::Vector2u frameIndex_{0, static_cast<unsigned>(id_)};
    float timer_{0.0f}; // tracks elapsed time
    unsigned fpr_{}; // frames per row
    float fps_{}; // frames per second  (by default is equal to fpr: "it takes one second to play every frame")
    float spf_{}; // seconds per frame
    Status status_{Status::READY};
    bool looping_{true};
};

#endif //BONK_GAME_ANIMATION_HPP
