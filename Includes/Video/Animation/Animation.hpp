#pragma once

#include <algorithm>
#include <SFML/Graphics/Rect.hpp>

#include "EnumSet.hpp"
#include "utils.hpp"


enum class AnimationStatus {
    READY, PLAYING, FINISHED
};

enum class AnimationMode {
    NORMAL, REVERSED
};

enum class AnimationPriority {
    DEFAULT, OVERLAY, OVERRIDE
};


struct Frame {
    sf::IntRect rect{};
    float duration{0.1f}; // [s]
};

using Frames = std::vector<Frame>;


inline Frames oneRowAnimation(const int row, const unsigned numberOfFrames, const sf::Vector2i frameSize,
                              const float duration) noexcept {
    Frames frames{};
    for (int i = 0; i < numberOfFrames; i++) {
        frames.emplace_back(Frame{sf::IntRect{{frameSize.x * i, frameSize.y * row}, frameSize}, duration});
    }
    return frames;
}

template<EnumSetConcept AnimationSet>
class Animation {
    using Status = AnimationStatus;

public:
    Animation(
        const typename AnimationSet::ID id,
        const Frames &&frames,
        const bool looping = true,
        const AnimationMode mode = AnimationMode::NORMAL,
        const AnimationPriority priority = AnimationPriority::DEFAULT
    )
        : id_(id),
          frames_(frames),
          priority_(priority),
          looping_(looping) {
        if (mode == AnimationMode::REVERSED) {
            std::ranges::reverse(frames_);
        }
    }

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
    void reset() noexcept;

    // GETTERS
    [[nodiscard]] typename AnimationSet::ID id() const noexcept;

    [[nodiscard]] AnimationPriority priority() const noexcept;

    [[nodiscard]] const Frame &currentFrame() const noexcept;

    [[nodiscard]] const AnimationStatus &status() const noexcept;

    void pause() noexcept;

    // UPDATE
    void play(float dt) noexcept;

private:
    typename AnimationSet::ID id_{0};
    unsigned index_{0};
    Frames frames_{};
    utils::StopWatch stopWatch_{utils::SILENT};
    Status status_{Status::READY};
    AnimationPriority priority_{AnimationPriority::DEFAULT};
    bool paused_{false};
    bool looping_{true};
};


template<EnumSetConcept AnimationSet>
void Animation<AnimationSet>::reset() noexcept {
    status_ = Status::READY;
    index_ = 0;
}

template<EnumSetConcept AnimationSet>
typename AnimationSet::ID Animation<AnimationSet>::id() const noexcept { return id_; }

template<EnumSetConcept AnimationSet>
AnimationPriority Animation<AnimationSet>::priority() const noexcept { return priority_; }

template<EnumSetConcept AnimationSet>
const Frame &Animation<AnimationSet>::currentFrame() const noexcept { return frames_.at(index_); }

template<EnumSetConcept AnimationSet>
const AnimationStatus &Animation<AnimationSet>::status() const noexcept { return status_; }

template<EnumSetConcept AnimationSet>
void Animation<AnimationSet>::pause() noexcept {
    paused_ = true;
}

template<EnumSetConcept AnimationSet>
void Animation<AnimationSet>::play(const float dt) noexcept {
    if (paused_) return;
    if (status_ == Status::FINISHED) {
        return;
    }
    status_ = Status::PLAYING;
    stopWatch_.tick(dt);
    // When it is the time to move to the next frame
    if (stopWatch_.getTime() >= currentFrame().duration) {
        stopWatch_.setTime(stopWatch_.getTime() - currentFrame().duration); // Consume spent time (reset timer)
        index_++;
    }
    // Evaluate the end of animationManager
    if (index_ >= frames_.size()) {
        // LOOP
        if (looping_) index_ = 0;
        // DONT LOOP
        else {
            index_ = frames_.size() - 1;
            status_ = Status::FINISHED;
        }
    }
}
