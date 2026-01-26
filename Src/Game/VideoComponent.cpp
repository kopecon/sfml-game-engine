//
// Created by Andrew on 29/11/2025.
//

#include "../../Includes/Game/VideoComponent.hpp"
#include "../../Includes/World/World.hpp"


VideoComponent::VideoComponent() = default;

VideoComponent::VideoComponent(const std::string &title)
    : windowTitle_(title),
    settings_(24, 8, 4, 3, 0),   // depth, stencil, antiAlias, major, minor
    window_(sf::VideoMode(initialWindowSize_), title, sf::Style::Default, windowState_, settings_),
    camera_(window_)
{
    window_.setFramerateLimit(fps_);
}

const sf::RenderWindow& VideoComponent::getWindow() {
    return window_;
}

void VideoComponent::recreateWindow() {
    window_.create(sf::VideoMode(initialWindowSize_), windowTitle_, sf::Style::Default, windowState_, settings_);
}

void VideoComponent::onClose(const sf::Event::Closed &) {
    // Pre-closing procedures implement here.
    window_.close();
}

void VideoComponent::onKeyPressed(const sf::Event::KeyPressed &keyPressed) {
    switch (keyPressed.scancode)
    {
        case sf::Keyboard::Scancode::Escape : window_.close(); break;
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

sf::Vector2u VideoComponent::getScreenSize() {
    return sf::VideoMode::getDesktopMode().size;
}

Camera & VideoComponent::getCamera() {
    return camera_;
}

sf::Vector2u VideoComponent::getWindowSize() const {
    return window_.getSize();
}

sf::Vector2f VideoComponent::getWindowToScreenRatio() const {
    return hd::divide(getWindowSize(), getScreenSize());
}

void VideoComponent::update(World *pWorld) {
    window_.handleEvents(
        [&](const sf::Event::Closed &event){onClose(event);},
        [&](const sf::Event::KeyPressed &keyPressed){onKeyPressed(keyPressed);}
    );

    // Update the view to follow the target
    camera_.followTarget();
    window_.setView(camera_.view);

    // --- Draw on screen ---
    window_.clear();

    if (pWorld) {
        for (auto const &entity : *pWorld->getEntities() | std::views::values) {
            entity->render.update();
            window_.draw(entity->render);
        }
    }

    auto test_shape = sf::CircleShape(10.f);
    test_shape.setOrigin(test_shape.getGeometricCenter());
    test_shape.setFillColor(sf::Color(0, 255, 0));
    test_shape.setPosition({0.f, pWorld->groundLevel});
    window_.draw(test_shape);

    window_.display();
    // --- Draw on screen ---
}
