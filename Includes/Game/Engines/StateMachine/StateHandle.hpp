#ifndef BONK_GAME_STATE_HANDLE_HPP
#define BONK_GAME_STATE_HANDLE_HPP
#include "Utils/EnumSet.hpp"


template<EnumSetConcept StateSet>
struct StateHandle {
    StateHandle() = default;

    explicit StateHandle(typename StateSet::ID id)
        : id_(id),
          name_(StateSet::name(id)) {
    }

    [[nodiscard]] const typename StateSet::ID &id() const { return id_; }
    [[nodiscard]] std::string_view name() const { return name_; }

private:
    typename StateSet::ID id_{};
    std::string name_{};
};


#endif //BONK_GAME_STATE_HANDLE_HPP
