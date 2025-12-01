//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_VIDEOCOMPONENT_HPP
#define BONK_GAME_VIDEOCOMPONENT_HPP
#include <string>
#include <SFML/Graphics.hpp>

#include "Camera.hpp"


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
    ),
    camera(Camera(window))
    {
        window.setFramerateLimit(fps);
    }

    // METADATA
    std::string title{};

    // VIDEO SETTINGS
    sf::ContextSettings settings;
    unsigned int fps{144};
    sf::State windowState = sf::State::Windowed;  // Initial state when game starts

    sf::RenderWindow window;
    Camera camera;

};


#endif //BONK_GAME_VIDEOCOMPONENT_HPP