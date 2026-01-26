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
public:
    VideoComponent();
    explicit VideoComponent(const std::string &title);

    // ACTIONS
    // SETTERS
    void recreateWindow();
    // GETTERS
    const sf::RenderWindow& getWindow();
    sf::Vector2u getWindowSize() const;
    [[nodiscard]] sf::Vector2f getWindowToScreenRatio() const;
    static sf::Vector2u getScreenSize();
    Camera& getCamera();
    // UPDATE
    void update(World *pWorld);

private:
    // METADATA
    const std::string windowTitle_{};
    // HARDWARE PARAMETERS
    const sf::Vector2u screenSize_ = sf::VideoMode::getDesktopMode().size;
    // VIDEO SETTINGS
    sf::ContextSettings settings_;
    unsigned int fps_{144};
    // WINDOW
    float windowSizeRatio_ = 2.f;  // Screen size / window size
    sf::State windowState_ = sf::State::Windowed;  // Initial state when game starts
    sf::Vector2u initialWindowSize_ = static_cast<sf::Vector2u>(scalar::divide(screenSize_, windowSizeRatio_));
    sf::RenderWindow window_{};
    Camera camera_{};
    // ACTIONS
    void onClose(const sf::Event::Closed&);
    void onKeyPressed(const sf::Event::KeyPressed& keyPressed);
};


#endif //BONK_GAME_VIDEO_COMPONENT_HPP