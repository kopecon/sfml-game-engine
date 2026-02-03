//
// Created by Andrew on 26/01/2026.
//

#include "Game/World/Entity/Player/Components/States/Concentrating.hpp"
#include "Game/Game.hpp"


namespace player {
    Concentrating::Concentrating(Player &player) : PlayerState(player, StateSet::ID::CONCENTRATING) {
        // EDGES
        makeEdge(concentrate, IDLE);
        // ACTIONS
        addEnterAction(changeColor());
        addMainAction(levitate());
        addExitAction(resetColor());
    }

    Condition Concentrating::exit() const {
        auto &input = player_.getInput();
        return [&input]{return input.key(input.getControls().concentrate).pressed;};
    }

    Action Concentrating::changeColor() const {
        return [this] {
            player_.render.setColor(sf::Color::Cyan);
        };
    }

    Action Concentrating::resetColor() const {
        return [this]{player_.render.setColor(sf::Color::White);};
    }

    Action Concentrating::levitate() const {
        return [this] {
            player_.position.y = 200.f;
        };
    }
} // player