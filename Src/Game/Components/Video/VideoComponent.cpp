#include "Game/Game.hpp"
#include "Game/World/World.hpp"
#include "Game/Components/Video/VideoComponent.hpp"
#include "Game/Engines/SceneGraph/Composite.hpp"
#include "Game/Engines/SceneGraph/RectangleShape.hpp"
#include "Game/Engines/SceneGraph/Sprite.hpp"


VideoComponent::VideoComponent(Game &game, const std::string &title)
    : EventSubscriber(game.getEventHandler()),
      game_(game),
      windowTitle_(title),
      window_(videoMode_, title, sf::Style::Default, windowState_, settings_) {
    window_.setFramerateLimit(fps_);
    initWindowSprite();
    // window_.setVerticalSyncEnabled(true);
}


void VideoComponent::recreateWindow() {
    window_.create(sf::VideoMode(videoMode_), windowTitle_, sf::Style::Default, windowState_, settings_);
}

const sf::RenderWindow &VideoComponent::getWindow() const {
    return window_;
}

sf::Vector2u VideoComponent::getWindowSize() const {
    return window_.getSize();
}

sf::Vector2f VideoComponent::getWindowToScreenRatio() const {
    return hd::divide(getWindowSize(), getScreenSize());
}

sf::Vector2u VideoComponent::getScreenSize() {
    return sf::VideoMode::getDesktopMode().size;
}

const Camera &VideoComponent::getCamera() const {
    return camera_;
}

Camera &VideoComponent::getCamera() {
    return camera_;
}

std::vector<sf::Event> &VideoComponent::getEvents() {
    return frameEvents_;
}

void VideoComponent::update() {
    // Save current events into frameEvents_.
    pollEvents();

    camera_.update();

    beginFrame();

    draw();

    endFrame();
}

void VideoComponent::initWindowSprite() {
    const auto winSize = static_cast<sf::Vector2f>(window_.getSize());
    const auto scale2D = hd::divide(winSize, GAME_RESOLUTION);

    auto scale = static_cast<float>(std::min(scale2D.x, scale2D.y));

    windowSprite_.setScale({scale, scale});

    const sf::Vector2f offset = (winSize - static_cast<sf::Vector2f>(GAME_RESOLUTION) * scale) / 2.f;

    windowSprite_.setPosition(offset);
}

void VideoComponent::beginFrame() {
    renderTexture_.clear();
}

// ---------------------------------------------------------------------------------------------------------------------
void VideoComponent::draw() {
    for (auto const &entity: *game_.getCurrentWorld().getEntities() | std::views::values) {
        renderTexture_.draw(entity->getRender());
    }

    // sf::CircleShape test_shape{10.f};
    // test_shape.setOrigin(test_shape.getGeometricCenter());
    // test_shape.setFillColor(sf::Color(0, 255, 0));
    // test_shape.setPosition(sf::Vector2f(0.f, BASE_CENTER.y));
    // renderTexture_.draw(test_shape);

    RectangleShape testShape{{10.f, 10.f}};
    testShape.setOrigin(testShape.getCenter());
    testShape.setColor(sf::Color(0, 255, 0));
    testShape.setPosition(sf::Vector2f(0.f, BASE_CENTER.y));
    renderTexture_.draw(testShape);
}
// ---------------------------------------------------------------------------------------------------------------------

void VideoComponent::endFrame() {
    renderTexture_.display();
    window_.clear();
    windowSprite_.setTexture(renderTexture_.getTexture());
    window_.draw(windowSprite_);
    window_.display();
}

// ReSharper disable once CppDFAUnreachableFunctionCall (is reachable via lambda handler_)
void VideoComponent::handleClosing() {
    // Pre-closing procedures implement here. (saving etc...)
    window_.close();
}

void VideoComponent::handlePressedKey(const sf::Event::KeyPressed &keyPressed) {
    switch (keyPressed.scancode) {
        case sf::Keyboard::Scancode::Escape: {
            handleClosing();
            break;
        }
        case sf::Keyboard::Scancode::U: {
            if (windowState_ == sf::State::Windowed) {
                windowState_ = sf::State::Fullscreen;
            } else if (windowState_ == sf::State::Fullscreen) {
                windowState_ = sf::State::Windowed;
            }
            // Recreate the window
            recreateWindow();
        }
        default: {
        }
    }
}

void VideoComponent::pollEvents() {
    frameEvents_.clear();
    while (const std::optional event = window_.pollEvent()) {
        if (!event) return;
        frameEvents_.push_back(*event);
    }
}

void VideoComponent::handleEvent(const sf::Event &event) {
    if (event.is<sf::Event::Closed>()) {
        handleClosing();
    }
    if (const auto keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        handlePressedKey(*keyPressed);
    }
}
