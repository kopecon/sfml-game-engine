#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Includes/Player.hpp"
#include "../Includes/Background.hpp"
#include "../Includes/Camera.hpp"
#include <iostream>


int main() {
#pragma region window settup

    constexpr auto title = "Bonk Game";
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    [[maybe_unused]] bool fullscreen = false;  // [[maybe_unused]] to prevent cLion from complaining
    auto windowState = sf::State::Windowed;

    // Create the window
    auto window = sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), title,
        sf::Style::Default,
        windowState,
        settings);

    window.setFramerateLimit(144);

#pragma endregion

#pragma region background
    sf::Texture backgroundTexture(RESOURCES_PATH "Custom/background.jpg");
    sf::Texture groundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_center.png");
    sf::Texture topGroundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_top.png");
    scenery::Background background_1(backgroundTexture, groundTexture, topGroundTexture,
        {
        window.getSize().x*3,
        window.getSize().y
    });

#pragma endregion

#pragma region player
    auto playerTexture(sf::Texture(RESOURCES_PATH "Custom/AnimationSheet_Character.png"));
    Player player_1(playerTexture, {
    sf::Keyboard::Scancode::A,
    sf::Keyboard::Scancode::D,
    sf::Keyboard::Scancode::W,
    sf::Keyboard::Scancode::LShift,
    sf::Keyboard::Scancode::F
});
    player_1.setPosition({background_1.shape.getGeometricCenter().x-200,
        background_1.floor.top.getPosition().y-player_1.size.y/2.f});
    player_1.physics.GROUND_LEVEL = player_1.position.y;
    Player player_2(playerTexture, {
        sf::Keyboard::Scancode::Left,
        sf::Keyboard::Scancode::Right,
        sf::Keyboard::Scancode::Up,
        sf::Keyboard::Scancode::RShift,
        sf::Keyboard::Scancode::Numpad0
    });
    player_2.shape.setFillColor(sf::Color({10,100,250}));
    player_2.setPosition({background_1.shape.getGeometricCenter().x+200,
        background_1.floor.top.getPosition().y-player_2.size.y/2.f});
    player_2.physics.GROUND_LEVEL = player_2.position.y;

#pragma endregion

#pragma region window events

    auto close = [&window]
    {
        window.close();
    };

    const auto onClose = [close](const sf::Event::Closed&)
    {
        close();
    };

    const auto onKeyPressed = [&close, &window, &windowState, &settings, &fullscreen]
    (const sf::Event::KeyPressed& keyPressed)
    {
        switch (keyPressed.scancode)
        {
            case sf::Keyboard::Scancode::Escape : close(); break;
            case sf::Keyboard::Scancode::U :
                {
                    fullscreen = !fullscreen;
                    if (fullscreen) {
                        windowState = sf::State::Fullscreen;
                    }
                    else if (!fullscreen) {
                        windowState = sf::State::Windowed;
                    }
                    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), title,
                    sf::Style::Default,
                    windowState,
                    settings);
                }
            default: {
            }
        }
    };

#pragma endregion

#pragma region update

    auto update = [&player_1, &player_2](const float &dt) {
        player_1.update(dt);
        // player_2.update(dt);
    };

#pragma endregion

    sf::Clock clock;
    tools::Camera camera(window);

    sf::Music music(RESOURCES_PATH "Audio/Midnight Forest.mp3");
    music.setVolume(1);
    music.setLooping(true);
    music.setLoopPoints({sf::milliseconds(0), sf::seconds(3*60)});
    // music.play();

#pragma region window loop
    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds(); // seconds since last frame

        window.handleEvents(onClose, onKeyPressed);

        // Update data
        update(dt);
        background_1.loop(camera);

        // Camera
        camera.follow_point(player_1.shape.getPosition());

        // Update the view to follow player
        window.setView(camera.view);

        // Clear and draw
        window.clear();
        window.draw(background_1.shape);
        window.draw(background_1.floor.body);
        window.draw(background_1.floor.top);
        window.draw(player_1.shape);
        window.draw(player_2.shape);
        window.display();
    }
#pragma endregion
}