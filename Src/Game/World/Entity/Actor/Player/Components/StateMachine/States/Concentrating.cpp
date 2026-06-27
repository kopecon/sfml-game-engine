#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Concentrating.hpp"


namespace player {
    Concentrating::Concentrating(Player &player) : DefaultState(player, DefaultStateSet::ID::CONCENTRATING) {
        // EDGES
        makeEdge(eval::SlotsPressed({{concentration_}}), IDLE);
        // ACTIONS
        addAction(ENTER_ACTION(changeColor));
        addAction(EXIT_ACTION(resetColor));
    }

    void Concentrating::changeColor() {
            this->player().getRenderManager().getMainSprite().setColor(sf::Color::Cyan);
    }

    void Concentrating::resetColor() {
        this->player().getRenderManager().getMainSprite().setColor(sf::Color::White);
    }
} // player
