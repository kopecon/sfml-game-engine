//
// Created by Andrew on 26/01/2026.
//

#include "../../../../Includes/Entity/Player/States/Concentrating.hpp"
#include "../../../../Includes/Game/Game.hpp"


namespace player {
    Concentrating::Concentrating(Player &player) : PlayerState(player, StateSet::ID::CONCENTRATING) {
        // EDGES
        addEdge(std::make_unique<Edge>(exit(), StateSet::ID::IDLE));
        addEnterAction(changeColor());
        addAction(levitate());
        addExitAction(resetColor());
    }

    Condition Concentrating::exit() const {
        auto &controls = player_.getInput().getControls();
        auto &input = player_.game.getInput();
        return [&controls, &input]{return input.key(controls.concentrate).pressed;};
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