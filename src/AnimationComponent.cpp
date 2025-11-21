//
// Created by Andrew on 17/11/2025.
//

#include "../Includes/AnimationComponent.hpp"

#include <iostream>

#include "../Includes/Player.hpp"


[[nodiscard]] sf::Vector2i AnimationSheet::getFrameSize(const int &framesPerRow, const int &framesPerColumn) const {
    auto x = static_cast<int>(pTexture->getSize().x / framesPerRow);
    auto y = static_cast<int>(pTexture->getSize().y / framesPerColumn);
    return {x, y};
}

AnimationEntry::AnimationEntry() = default;

AnimationEntry::AnimationEntry(const int &id, const int &framesPerRow, const bool &looping):
    id(id), framesPerRow(framesPerRow), fps(static_cast<float>(framesPerRow)), looping(looping) {}

AnimationEntry::AnimationEntry(const int &id, const int &framesPerRow, const float &fps, const bool &looping):
    id(id), framesPerRow(framesPerRow), fps(fps), looping(looping) {}

bool AnimationEntry::operator!=(const AnimationEntry &other) const {
    return this->id != other.id;
}

bool AnimationEntry::operator==(const AnimationEntry &other) const {
    return this->id == other.id;
}

size_t AnimationEntry::Hash::operator()(const AnimationEntry &anim) const noexcept {
    return std::hash<int>()(anim.id);
}

AnimationComponent::AnimationComponent() = default;

AnimationComponent::AnimationComponent(const AnimationSheet &animationSheet): animationSheet(animationSheet) {}

void AnimationComponent::set(const int &animationID) {
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
        pCurrentAnimation->state = AnimationEntry::READY;
    }
}

void AnimationComponent::add(const AnimationEntry &animation) {
    animationSet.emplace(animation.id, animation);

    if (pCurrentAnimation == nullptr) {
        set(animation.id);
    }
}

void AnimationComponent::update(entities::Player &player, const float &dt) {
    selectAnimation(player);
    player.shape.setTextureRect(getFrame());
    pCurrentAnimation->state = AnimationEntry::PLAYING;
    pCurrentAnimation->timer += dt;
    // When it is the time to move to the next frame
    if (pCurrentAnimation->timer >= 1/pCurrentAnimation->fps) {
        pCurrentAnimation->frameIndex.x += 1;
        pCurrentAnimation->timer = 0.f;  // Reset timer
    }
    // Evaluate the end of animation
    if (pCurrentAnimation->frameIndex.x+1 > pCurrentAnimation->framesPerRow) {
        // LOOP
        if (pCurrentAnimation->looping) pCurrentAnimation->frameIndex.x = 0;
        // DONT LOOP
        else {
            pCurrentAnimation->state = AnimationEntry::FINISHED;
            pCurrentAnimation = pPreviousAnimation;  // Continue previous animation such as "Idle" etc...
        }
    }
}

sf::IntRect AnimationComponent::getFrame() const {
    auto frameCoord = sf::Vector2i(
        pCurrentAnimation->frameIndex.x*animationSheet.frameSize.x,
        pCurrentAnimation->frameIndex.y*animationSheet.frameSize.y
    );
    return {frameCoord, animationSheet.frameSize};
}

void AnimationComponent::selectAnimation(const entities::Player &player) {
    using enum entities::Player::PlayerAnimations;
    using enum entities::Player::PlayerStates;
    switch (player.state) {
        case JUMPING : {
            set(JUMP);
            animationSet[JUMP].fps = std::fabs(player.maxWalkingSpeed.y / player.maxSpeed.y)*24.f;
            break;
        }
        case WALKING : {
            set(WALK);
            pCurrentAnimation->fps = std::fabs(player.velocity.x / player.maxWalkingSpeed.x) * static_cast<float>(pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case RUNNING : {
            set(RUN);
            pCurrentAnimation->fps = std::fabs(player.velocity.x / player.maxRunningSpeed.x) * static_cast<float>(pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        default: {
            set(IDLE);
        }
    }
}