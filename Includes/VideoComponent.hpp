//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_VIDEOCOMPONENT_HPP
#define BONK_GAME_VIDEOCOMPONENT_HPP
#include <SFML/Graphics.hpp>
#include "Camera.hpp"

class World;


class VideoComponent {
public:
    VideoComponent();
    explicit VideoComponent(const std::string &title);

    // METADATA
    std::string title{};

    // VIDEO SETTINGS
    sf::ContextSettings settings;
    sf::Vector2u screenSize = sf::VideoMode::getDesktopMode().size;
    const sf::Vector2u initScreenSize{static_cast<unsigned>(screenSize.x/2.f), static_cast<unsigned>(screenSize.y/2.f)};
    unsigned int fps{144};
    sf::State windowState = sf::State::Windowed;  // Initial state when game starts

    sf::RenderWindow window{};
    Camera camera{};

    void recreate();

    void onClose(const sf::Event::Closed&);

    void onKeyPressed(const sf::Event::KeyPressed& keyPressed);

    void update(World &world);
};


#endif //BONK_GAME_VIDEOCOMPONENT_HPP