//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP
#include <string>

class Player;


class State {
protected:
    Player *pPlayer{nullptr};
public:
    virtual ~State();
    explicit State(std::string name);
    explicit State(Player &player, std::string name);

    std::string name{};

    virtual void act() = 0;
};

#endif //BONK_GAME_STATE_HPP
