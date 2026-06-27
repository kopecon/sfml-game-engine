#ifndef BONK_GAME_VIDEO_COMPONENT_HPP
#define BONK_GAME_VIDEO_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "Utils/customTypes.hpp"
#include "Utils/utils.hpp"
#include "Game/Engines/EventHandling/EventHandler.hpp"
#include "Game/Components/Video/Camera.hpp"


class Game;
class World;


class VideoComponent final : public EventSubscriber{
public:
    explicit VideoComponent(Game& game, const std::string &title);

    // SETTERS
    void recreateWindow();
    // GETTERS
    [[nodiscard]] const sf::RenderWindow& getWindow() const;
    [[nodiscard]] sf::Vector2u getWindowSize() const;
    [[nodiscard]] sf::Vector2f getWindowToScreenRatio() const;
    [[nodiscard]] static sf::Vector2u getScreenSize();
    [[nodiscard]] const Camera& getCamera() const;
    [[nodiscard]] Camera& getCamera();
    [[nodiscard]] std::vector<sf::Event>& getEvents();
    // UPDATE
    void update();

private:
    // REFERENCES
    Game& game;
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
    // EVENTS
    std::vector<sf::Event> frameEvents_;
    // ACTIONS
    void handleClosing();
    void handlePressedKey(const sf::Event::KeyPressed &keyPressed);
    // UPDATE
    void pollEvents();
    void handleEvent(const sf::Event &event) override;
};


#endif //BONK_GAME_VIDEO_COMPONENT_HPP