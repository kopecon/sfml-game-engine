#pragma once
#include <concepts>


namespace state_machine {
    class Domain {
    };
}


template<typename T>
concept IsStateDomain = std::derived_from<T, state_machine::Domain>;