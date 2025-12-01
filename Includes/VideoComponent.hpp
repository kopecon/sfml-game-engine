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
    const sf::Vector2u initScreenSize{800, 600};
    unsigned int fps{144};
    sf::State windowState = sf::State::Windowed;  // Initial state when game starts

    sf::RenderWindow window{};
    Camera camera{};

    void recreate();

    void onClose(const sf::Event::Closed&);

    void onKeyPressed(const sf::Event::KeyPressed& keyPressed) {
        switch (keyPressed.scancode)
        {
            case sf::Keyboard::Scancode::Escape : window.close(); break;
            case sf::Keyboard::Scancode::U :
            {
                if (windowState == sf::State::Windowed) {
                    windowState = sf::State::Fullscreen;
                }
                else if (windowState == sf::State::Fullscreen) {
                    windowState = sf::State::Windowed;
                }
                // Recreate the window
                recreate();
            }
            default: {
            }
        }
    }

    void update(const World &world);
};


#endif //BONK_GAME_VIDEOCOMPONENT_HPP