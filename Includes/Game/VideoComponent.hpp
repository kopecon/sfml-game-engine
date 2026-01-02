//
// Created by Andrew on 29/11/2025.
//

#ifndef BONK_GAME_VIDEO_COMPONENT_HPP
#define BONK_GAME_VIDEO_COMPONENT_HPP
#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "../../Utils/utils.hpp"

class World;


class VideoComponent {
    // METADATA
    const std::string windowTitle{};
    // HARDWARE PARAMETERS
    sf::Vector2u screenSize = sf::VideoMode::getDesktopMode().size;
    // VIDEO SETTINGS
    sf::ContextSettings settings;
    unsigned int fps{144};
    // WINDOW
    float windowSizeRatio = 2.f;  // Screen size / window size
    sf::State windowState = sf::State::Windowed;  // Initial state when game starts
    sf::Vector2u initialWindowSize = scalar::divide(screenSize, windowSizeRatio);
    sf::RenderWindow window{};

public:
    VideoComponent();

    explicit VideoComponent(const std::string &title);

    // COMPONENTS
    Camera camera{};

protected:
    void onClose(const sf::Event::Closed&);

    void onKeyPressed(const sf::Event::KeyPressed& keyPressed);

public:
    const sf::RenderWindow& getWindow();

    void recreateWindow();

    void update(World *pWorld);
};


#endif //BONK_GAME_VIDEO_COMPONENT_HPP