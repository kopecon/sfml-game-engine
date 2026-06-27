#ifndef BONK_GAME_STATEMACHINE_CONTEXT_HPP
#define BONK_GAME_STATEMACHINE_CONTEXT_HPP

#include "Game/Engines/StateMachine/StateHandle.hpp"


template<EnumSetConcept StateSet>
struct StateMachineContext {
    StateHandle<StateSet> from{};
};


#endif //BONK_GAME_STATEMACHINE_CONTEXT_HPP
