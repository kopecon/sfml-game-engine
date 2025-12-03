//
// Created by Andrew on 29/11/2025.
//

#include "../../Includes/Game/VideoComponent.hpp"
#include "../../Includes/World/World.hpp"


VideoComponent::VideoComponent() = default;

VideoComponent::VideoComponent(const std::string &title)
    : title(title),
    settings(24, 8, 4, 3, 0),   // depth, stencil, antiAlias, major, minor
    window(sf::VideoMode(windowSize), title, sf::Style::Default, windowState, settings),
    camera(window)
{
    window.setFramerateLimit(fps);
}

void VideoComponent::recreate() {
    window.create(sf::VideoMode(windowSize), title, sf::Style::Default, windowState, settings);
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
                windowSize = screenSize;
                windowState = sf::State::Fullscreen;
            }
            else if (windowState == sf::State::Fullscreen) {
                windowSize = {
                    static_cast<unsigned>(static_cast<float>(screenSize.x)/windowSizeRatio),
                    static_cast<unsigned>(static_cast<float>(screenSize.y)/windowSizeRatio),
                };
                windowState = sf::State::Windowed;
            }
            // Recreate the window
            recreate();
        }
        default: {
        }
    }
}

void VideoComponent::update(World *world) {
    window.handleEvents(
        [&](const sf::Event::Closed &event){onClose(event);},
        [&](const sf::Event::KeyPressed &keyPressed){onKeyPressed(keyPressed);}
    );


    // Update entities in the world
    world->update();

    // Update the view to follow the target
    if (camera.pTarget != nullptr) camera.followTarget();
    window.setView(camera.view);

    // Draw on screen
    window.clear();
    world->draw();
    window.display();
}
