//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATION_ENGINE_HPP
#define BONK_GAME_ANIMATION_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Animation.hpp"


class Composite;
class AnimationSheet;


class AnimationEngine {
    sf::Sprite *pTarget_;
    std::unique_ptr<AnimationSheet> animationSheet_;
    std::unordered_map<animation_id, std::unique_ptr<Animation>> animations_;
    Animation *pCurrentAnimation_{nullptr};

public:
#pragma region constructors
    explicit AnimationEngine(sf::Sprite &target, std::unique_ptr<AnimationSheet> animationSheet);
    explicit AnimationEngine(const Composite &composite);
    explicit AnimationEngine(const Composite &composite, std::unique_ptr<AnimationSheet> animationSheet);
#pragma endregion

    [[nodiscard]] sf::IntRect getCurrentFrame() const;


    void add(std::unique_ptr<Animation> animation);

    void set(const animation_id &id);

    [[nodiscard]] Animation* getCurrentAnimation() const;

    void update(const float &dt) const;
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP