#ifndef BONK_GAME_TIME_COMPONENT_HPP
#define BONK_GAME_TIME_COMPONENT_HPP

#include "SFML/System/Clock.hpp"


class TimeComponent {
public:
    [[nodiscard]] float dt() const;
    void update();

private:
    sf::Clock clock_{};
    float dt_{};
};


#endif //BONK_GAME_TIME_COMPONENT_HPP