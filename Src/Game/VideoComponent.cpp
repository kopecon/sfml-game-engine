//
// Created by Andrew on 29/11/2025.
//

#include "../../Includes/Game/VideoComponent.hpp"
#include "../../Includes/World/World.hpp"


VideoComponent::VideoComponent() = default;

VideoComponent::VideoComponent(const std::string &title)
    : windowTitle(title),
    settings(24, 8, 4, 3, 0),   // depth, stencil, antiAlias, major, minor
    window(sf::VideoMode(initialWindowSize), title, sf::Style::Default, windowState, settings),
    camera(window)
{
    window.setFramerateLimit(fps);
}

const sf::RenderWindow& VideoComponent::getWindow() {
    return window;
}

void VideoComponent::recreateWindow() {
    window.create(sf::VideoMode(initialWindowSize), windowTitle, sf::Style::Default, windowState, settings);
}

void VideoComponent::onClose(const sf::Event::Closed &) {
    // Pre-closing procedures implement here.
    window.close();
}

void VideoComponent::onKeyPressed(const sf::Event::KeyPressed &keyPressed) {
    switch (keyPressed.scancode)
    {
        case sf::Keyboard::Scancode::Escape : window.close(); break;
        case sf::Keyboard::Scancode::U :
        {
            if (windowState == sf::State::Windowed) {
                initialWindowSize = screenSize;
                windowState = sf::State::Fullscreen;
            }
            else if (windowState == sf::State::Fullscreen) {
                initialWindowSize = {
                    static_cast<unsigned>(static_cast<float>(screenSize.x)/windowSizeRatio),
                    static_cast<unsigned>(static_cast<float>(screenSize.y)/windowSizeRatio),
                };
                windowState = sf::State::Windowed;
            }
            // Recreate the window
            recreateWindow();
        }
        default: {
        }
    }
}

void VideoComponent::update(World *pWorld) {
    window.handleEvents(
        [&](const sf::Event::Closed &event){onClose(event);},
        [&](const sf::Event::KeyPressed &keyPressed){onKeyPressed(keyPressed);}
    );

    // Update the view to follow the target
    camera.followTarget();
    window.setView(camera.view);

    // --- Draw on screen ---
    window.clear();

    if (pWorld) {
        for (auto const &entity : *pWorld->getEntities() | std::views::values) {
            entity->render.update();
            window.draw(entity->render.root);
        }
    }

    auto test_shape = sf::CircleShape(10.f);
    test_shape.setOrigin(test_shape.getGeometricCenter());
    test_shape.setFillColor(sf::Color(0, 255, 0));
    test_shape.setPosition({0.f, pWorld->groundLevel});
    window.draw(test_shape);

    window.display();
    // --- Draw on screen ---
}
