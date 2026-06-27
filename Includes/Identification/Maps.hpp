#pragma once

#include <map>
#include <unordered_map>

#include "Identification/StrongType.hpp"


namespace identity {
    template<typename Type, typename Value>
    using UMap = std::unordered_map<ID<Type>, Value, typename ID<Type>::Hash>;

    template<typename Type, typename Value>
    using InstanceUMap = std::unordered_map<InstanceID<Type>, Value, typename ID<Type>::Hash>;

    template<typename Type, typename Value>
    using OMap = std::map<ID<Type>, Value>;

    template<typename Type, typename Value>
    using InstanceOMap = std::map<InstanceID<Type>, Value>;
}