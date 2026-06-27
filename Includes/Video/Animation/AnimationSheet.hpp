#pragma once

#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>

#include "Video/Animation/Animation.hpp"


template<EnumSetConcept AnimationSet>
struct AnimationSheet {
    using AnimID = typename AnimationSet::ID;

    const sf::Texture &texture{};
    std::unordered_map<AnimID, std::unique_ptr<Animation<AnimationSet> > > animations_;

    explicit AnimationSheet(const sf::Texture &texture);

    Animation<AnimationSet> &addAnimation(std::unique_ptr<Animation<AnimationSet> > animation) noexcept;
};

template<EnumSetConcept AnimationSet>
AnimationSheet<AnimationSet>::AnimationSheet(const sf::Texture &texture)
    : texture(texture) {
}

template<EnumSetConcept AnimationSet>
Animation<AnimationSet> &AnimationSheet<AnimationSet>::addAnimation(
    std::unique_ptr<Animation<AnimationSet> > animation) noexcept {
    const auto id = animation->id();
    animations_.emplace(id, std::move(animation));
    return *animations_.at(id);
}
