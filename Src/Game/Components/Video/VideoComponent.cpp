//
// Created by Andrew on 29/11/2025.
//

#include "Game/Game.hpp"
#include "Game/World/World.hpp"
#include "Game/Components/Video/VideoComponent.hpp"


VideoComponent::VideoComponent(Game& game, const std::string &title) :
    EventSubscriber(game.getEventHandler()),
    game(game),
    windowTitle_(title),
    settings_(24, 8, 4, 3, 0),   // depth, stencil, antiAlias, major, minor
    window_(sf::VideoMode(initialWindowSize_), title, sf::Style::Default, windowState_, settings_),
    camera_(window_) {
    window_.setFramerateLimit(fps_);
}


void VideoComponent::recreateWindow() {
    window_.create(sf::VideoMode(initialWindowSize_), windowTitle_, sf::Style::Default, windowState_, settings_);
}

const sf::RenderWindow& VideoComponent::getWindow() {
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

Camera & VideoComponent::getCamera() {
    return camera_;
}

std::vector<sf::Event> & VideoComponent::getEvents() {
    return frameEvents_;
}

void VideoComponent::update() {
    // Save current events into frameEvents_.
    pollEvents();

    // Update the view to follow the target
    camera_.followTarget();
    window_.setView(camera_.view);

    // --- Draw on screen ---
    window_.clear();

    for (auto const &entity : *game.getCurrentWorld().getEntities() | std::views::values) {
        entity->render.update();  // TODO: review and find proper place to update render
        window_.draw(entity->render);
    }

    auto test_shape = sf::CircleShape(10.f);
    test_shape.setOrigin(test_shape.getGeometricCenter());
    test_shape.setFillColor(sf::Color(0, 255, 0));
    test_shape.setPosition({0.f, game.getCurrentWorld().groundLevel});
    window_.draw(test_shape);

    window_.display();
    // --- Draw on screen ---
}

// ReSharper disable once CppDFAUnreachableFunctionCall (is reachable via lambda handler_)
void VideoComponent::handleClosing() {
    // Pre-closing procedures implement here. (saving etc...)
    window_.close();
}

void VideoComponent::handlePressedKey(const sf::Event::KeyPressed &keyPressed) {
    switch (keyPressed.scancode) {
        case sf::Keyboard::Scancode::Escape : {
            handleClosing();
            break;
        }
        case sf::Keyboard::Scancode::U :
        {
            if (windowState_ == sf::State::Windowed) {
                initialWindowSize_ = screenSize_;
                windowState_ = sf::State::Fullscreen;
            }
            else if (windowState_ == sf::State::Fullscreen) {
                initialWindowSize_ = {
                    static_cast<unsigned>(static_cast<float>(screenSize_.x)/windowSizeRatio_),
                    static_cast<unsigned>(static_cast<float>(screenSize_.y)/windowSizeRatio_),
                };
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
