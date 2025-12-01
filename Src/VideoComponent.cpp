//
// Created by Andrew on 29/11/2025.
//

#include "../Includes/VideoComponent.hpp"
#include "../Includes/World.hpp"


VideoComponent::VideoComponent() = default;

VideoComponent::VideoComponent(const std::string &title)
    : title(title),
    settings(24, 8, 4, 3, 0),   // depth, stencil, antiAlias, major, minor
    window(sf::VideoMode(initScreenSize), title, sf::Style::Default, windowState, settings),
    camera(window)
{
    window.setFramerateLimit(fps);
}

void VideoComponent::recreate() {
    window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Default, windowState, settings);
}

void VideoComponent::onClose(const sf::Event::Closed &) {
    // Pre-closing procedures implement here.
    window.close();
}

void VideoComponent::update(const World &world) {
    window.handleEvents(
        [&](const sf::Event::Closed &event){onClose(event);},
        [&](const sf::Event::KeyPressed &keyPressed){onKeyPressed(keyPressed);}
    );

    // Camera
    camera.followTarget();

    // Update the view to follow player
    window.setView(camera.view);

    window.clear();
    world.draw();
    window.display();
}
