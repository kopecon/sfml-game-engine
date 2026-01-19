//
// Created by Andrew on 27/12/2025.
//

#ifndef BONK_GAME_ENUM_SET_BASE_HPP
#define BONK_GAME_ENUM_SET_BASE_HPP
#include <string_view>

template<typename> struct EnumSetTraits;

template<typename Derived>
struct EnumSet {
    using ID = typename EnumSetTraits<Derived>::Enum;

    static std::string_view name(const ID state) {
        return EnumSetTraits<Derived>::name(state);
    }
private:
    // For safety make sure proper derivation took place
    EnumSet() = default;
    friend Derived;
};

template<typename T>
concept EnumSetConcept = requires(typename T::ID id) {
    {T::name(id)} -> std::convertible_to<std::string_view>;
};

#endif //BONK_GAME_ENUM_SET_BASE_HPP