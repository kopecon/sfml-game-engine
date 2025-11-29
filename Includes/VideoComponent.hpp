//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_VIDEOCOMPONENT_HPP
#define BONK_GAME_VIDEOCOMPONENT_HPP
#include <string>
#include <SFML/Graphics.hpp>


class VideoComponent {
public:
    explicit VideoComponent(const std::string &title)
    : title(title),
    settings(24, 8, 4, 3, 0),   // depth, stencil, antiAlias, major, minor
    window(
        sf::VideoMode::getDesktopMode(),
        title,
        sf::Style::Default,
        windowState,
        settings
    ) {
        window.setFramerateLimit(fps);
    }

    std::string title{};
    sf::ContextSettings settings;
    unsigned int fps{144};

    bool fullscreen = false;  // [[maybe_unused]] to prevent cLion from complaining
    sf::State windowState = sf::State::Windowed;

    sf::RenderWindow window;
};


#endif //BONK_GAME_VIDEOCOMPONENT_HPP