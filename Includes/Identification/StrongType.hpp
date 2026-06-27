#pragma once

#include <string>
#include <ostream>


namespace identity {
    template<typename T>
    struct StrongType {
        // NOTE: each ID starts at 1.
        // ID = 0 is a null (NONE) ID!
        StrongType();

        explicit StrongType(std::size_t value);

        [[nodiscard]] constexpr std::size_t value() const noexcept;

        [[nodiscard]] constexpr std::string as_string() const noexcept;

        auto operator<=>(const StrongType &) const = default;

        struct Hash {
            size_t operator()(const StrongType &id) const noexcept;
        };

        [[nodiscard]] static constexpr StrongType None() noexcept;

    private:
        friend T;
        const std::size_t value_;
    };

    template<typename T>
    StrongType<T>::StrongType() : value_(0) {
    }

    template<typename T>
    StrongType<T>::StrongType(const std::size_t value) : value_(value) {
    }

    template<typename T>
    constexpr std::size_t StrongType<T>::value() const noexcept {
        return value_;
    }

    template<typename T>
    constexpr std::string StrongType<T>::as_string() const noexcept {
        return std::to_string(value());
    }

    template<typename T>
    constexpr StrongType<T> StrongType<T>::None() noexcept {
        return StrongType{0};
    }

    template<typename T>
    size_t StrongType<T>::Hash::operator()(const StrongType &id) const noexcept {
        return std::hash<std::size_t>()(id.value());
    }

    template<typename T>
    struct InstanceID : StrongType<T> {
        using StrongType<T>::StrongType;

        [[nodiscard]] static constexpr InstanceID None() noexcept;
    };

    template<typename T>
    constexpr InstanceID<T> InstanceID<T>::None() noexcept {
        return InstanceID{0};
    }
}

template<typename T>
using ID = identity::StrongType<T>;

template<typename T>
using InstanceID = identity::InstanceID<T>;
