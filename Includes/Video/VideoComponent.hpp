#pragma once

#include <SFML/Graphics.hpp>

#include "EventHandling/EventHandler.hpp"
#include "Video/Camera.hpp"


class Engine;
class EntityManager;


class VideoComponent final : public EventSubscriber {
public:
    static constexpr sf::Vector2u GAME_RESOLUTION{1920/3, 1080/3};
    static constexpr sf::Vector2u BASE_CENTER{0, 0};

    explicit VideoComponent(Engine &engine, const std::string &title);

    // SETTERS
    void recreateWindow() noexcept;

    // GETTERS
    [[nodiscard]] const sf::RenderWindow &getWindow() const noexcept;

    [[nodiscard]] sf::Vector2u getWindowSize() const noexcept;

    [[nodiscard]] sf::Vector2f getWindowToScreenRatio() const;

    [[nodiscard]] static sf::Vector2u getScreenSize() noexcept;

    [[nodiscard]] const Camera &getCamera() const noexcept;

    [[nodiscard]] Camera &getCamera() noexcept;

    [[nodiscard]] sf::Vector2f windowToWorld(sf::Vector2i pos) const noexcept;

    [[nodiscard]] std::vector<sf::Event> &getEvents() noexcept;

    [[nodiscard]] sf::RenderTexture &renderTexture();

    // UPDATE
    void update() noexcept;

private:
    // REFERENCES
    Engine &engine_;
    // METADATA
    const std::string windowTitle_{};
    // HARDWARE PARAMETERS
    const sf::VideoMode desktopMode_{sf::VideoMode::getDesktopMode()};
    const sf::Vector2u screenSize_{desktopMode_.size};
    const unsigned screenBPP_{desktopMode_.bitsPerPixel};
    // VIDEO SETTINGS
    const sf::Vector2u windowSize_{1400, 1000}; // Set to desired number
    // const sf::Vector2u windowSize_{screenSize_};
    const sf::VideoMode videoMode_{windowSize_, screenBPP_};
    sf::State windowState_{sf::State::Windowed}; // Initial window state
    sf::ContextSettings settings_{24, 8, 4, 3, 0}; // depth, stencil, antiAlias, major, minor
    sf::RenderTexture renderTexture_{GAME_RESOLUTION};
    sf::Sprite windowSprite_{renderTexture_.getTexture()};
    sf::RenderWindow window_{};
    unsigned int fps_{144};
    // COMPONENTS
    Camera camera_{engine_};
    // EVENTS
    std::vector<sf::Event> frameEvents_{};

    // INIT
    void initWindowSprite() noexcept;

    // ACTIONS
    void beginFrame() noexcept;

    void draw() noexcept;

    void endFrame() noexcept;

    void handleClosing() noexcept;

    void handlePressedKey(const sf::Event::KeyPressed &keyPressed) noexcept;

    // UPDATE
    void pollEvents() noexcept;

    void handleEvent(const sf::Event &event) noexcept override;
};
