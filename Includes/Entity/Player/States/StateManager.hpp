//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_STATE_MANAGER_HPP
#define BONK_GAME_STATE_MANAGER_HPP
#include <memory>


class Player;
class State;


class StateManager {
public:enum class States {
    NONE = -1,
    IDLE,
    WINKING,
    WALKING,
    RUNNING,
    CROUCHING,
    JUMPING,
    DISAPPEARING,
    DYING,
    ATTACKING,
    BRAKING,
    STOPPING,
};
    StateManager();
    explicit StateManager(Player &player);

    Player *pPlayer{nullptr};
    std::unique_ptr<State> pState{nullptr};  // This refers to the actual state
    States state{States::IDLE};  // This just tags the current state so its "visible" to other modules
    States targetState{};  // Usually triggered by the user's input

    void act() const;
    void update() const;
};


#endif //BONK_GAME_STATE_MANAGER_HPP