#pragma once

#include <string_view>


template<typename>
struct EnumSetTraits;

template<typename Derived>
struct EnumSet {
    using ID = typename EnumSetTraits<Derived>::Enum;

    static std::string_view name(const ID state) noexcept;

private:
    // For safety make sure proper derivation took place
    EnumSet() = default;

    friend Derived;
};

template<typename Derived>
std::string_view EnumSet<Derived>::name(const ID state) noexcept {
    return EnumSetTraits<Derived>::name(state);
}

template<typename T>
concept Enum = std::is_enum_v<T>;

template<typename T>
concept EnumSetConcept = requires(typename T::ID id)
{
    { T::name(id) } -> std::convertible_to<std::string_view>;
};
