# pragma once

#include "SFML/System/Clock.hpp"


class TimeComponent {
public:
    [[nodiscard]] float dt() const;

    void update();

private:
    sf::Clock clock_{};
    float dt_{};
};
