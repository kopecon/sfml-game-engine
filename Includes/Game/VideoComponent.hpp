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
    // HARDWARE PARAMETERS
    sf::Vector2u screenSize = sf::VideoMode::getDesktopMode().size;
    // VIDEO SETTINGS
    sf::ContextSettings settings;
    float windowSizeRatio = 2.f;  // Screen size / window size
    unsigned int fps{144};
    // WINDOW
    sf::State windowState = sf::State::Windowed;  // Initial state when game starts
    sf::Vector2u windowSize = {
        static_cast<unsigned>(static_cast<float>(screenSize.x)/windowSizeRatio),
        static_cast<unsigned>(static_cast<float>(screenSize.y)/windowSizeRatio)};
    sf::RenderWindow window{};
    // COMPONENTS
    Camera camera{};

    void recreate();

    void onClose(const sf::Event::Closed&);

    void onKeyPressed(const sf::Event::KeyPressed& keyPressed);

    void update(World *world);
};


#endif //BONK_GAME_VIDEOCOMPONENT_HPP