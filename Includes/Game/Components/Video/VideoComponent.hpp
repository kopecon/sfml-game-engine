#ifndef BONK_GAME_VIDEO_COMPONENT_HPP
#define BONK_GAME_VIDEO_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "Utils/customTypes.hpp"
#include "Utils/utils.hpp"
#include "Game/Engines/EventHandling/EventHandler.hpp"
#include "Game/Components/Video/Camera.hpp"


class Render;
class Game;
class World;


class VideoComponent final : public EventSubscriber {
public:
    static constexpr sf::Vector2u GAME_RESOLUTION{640, 320};
    static constexpr sf::Vector2u BASE_CENTER{0, 0};

    explicit VideoComponent(Game &game, const std::string &title);

    // SETTERS
    void recreateWindow();

    // GETTERS
    [[nodiscard]] const sf::RenderWindow &getWindow() const;

    [[nodiscard]] sf::Vector2u getWindowSize() const;

    [[nodiscard]] sf::Vector2f getWindowToScreenRatio() const;

    [[nodiscard]] static sf::Vector2u getScreenSize();

    [[nodiscard]] const Camera &getCamera() const;

    [[nodiscard]] Camera &getCamera();

    [[nodiscard]] std::vector<sf::Event> &getEvents();

    // UPDATE
    void update();

private:
    // REFERENCES
    Game &game_;
    // METADATA
    const std::string windowTitle_{};
    // HARDWARE PARAMETERS
    const sf::VideoMode videoMode_{sf::VideoMode::getDesktopMode()};
    // VIDEO SETTINGS
    sf::ContextSettings settings_{24, 8, 4, 3, 0}; // depth, stencil, antiAlias, major, minor
    unsigned int fps_{144};
    // WINDOW
    sf::State windowState_ = sf::State::Windowed; // Initial window state
    sf::RenderWindow window_;
    sf::RenderTexture renderTexture_{GAME_RESOLUTION};
    sf::Sprite windowSprite_{renderTexture_.getTexture()};
    Camera camera_{renderTexture_};
    // EVENTS
    std::vector<sf::Event> frameEvents_;

    // INIT
    void initWindowSprite();

    // ACTIONS
    void beginFrame();

    void draw();

    void endFrame();

    void handleClosing();

    void handlePressedKey(const sf::Event::KeyPressed &keyPressed);

    // UPDATE
    void pollEvents();

    void handleEvent(const sf::Event &event) override;
};


#endif //BONK_GAME_VIDEO_COMPONENT_HPP
