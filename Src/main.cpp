#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Includes/Game.hpp"
#include "../Includes/World.hpp"
#include "../Includes/Player.hpp"
#include "../Includes/Background.hpp"
#include "../Includes/Ground.hpp"
#include "../Includes/Camera.hpp"
#include <iostream>


int main() {
#pragma region game settup
    const auto* title = "Bonk Game";
    Game game(title);

    // Reference the window
    sf::RenderWindow &window = game.videoComponent.window;

#pragma endregion

#pragma region background
    sf::Texture backgroundTexture(RESOURCES_PATH "Custom/background.jpg");
    Background background(backgroundTexture, {window.getSize().x*3,window.getSize().y});
    sf::Texture groundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_center.png");
    sf::Texture topGroundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_top.png");
    float groundLevel = window.getSize().y - window.getSize().y/5.f;
    Ground ground(groundTexture, topGroundTexture, {window.getSize().x*3, window.getSize().y}, groundLevel);
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
    player_1.setGroundLevel(groundLevel);
    player_1.setPosition({-250.f, player_1.physics.GROUND_LEVEL-player_1.size.y});
    Player player_2(playerTexture, {
        sf::Keyboard::Scancode::Left,
        sf::Keyboard::Scancode::Right,
        sf::Keyboard::Scancode::Up,
        sf::Keyboard::Scancode::RShift,
        sf::Keyboard::Scancode::Numpad0
    });
    player_2.shape.setFillColor(sf::Color({10,100,250}));
    player_2.setGroundLevel(groundLevel);
    player_2.setPosition({250.f, player_2.physics.GROUND_LEVEL-player_2.size.y});

#pragma endregion

#pragma region world
    World world{};
    world.add(background);
    world.add(ground);
    world.add(player_2);
    world.add(player_1);
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

    const auto onKeyPressed = [&close, &game](const sf::Event::KeyPressed& keyPressed) {
        switch (keyPressed.scancode)
        {
            case sf::Keyboard::Scancode::Escape : close(); break;
            case sf::Keyboard::Scancode::U :
                {
                    if (game.videoComponent.windowState == sf::State::Windowed) {
                        game.videoComponent.windowState = sf::State::Fullscreen;
                    }
                    else if (game.videoComponent.windowState == sf::State::Fullscreen) {
                        game.videoComponent.windowState = sf::State::Windowed;
                    }
                    // Recreate the window
                    game.videoComponent.window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), game.videoComponent.title,
                    sf::Style::Default,
                    game.videoComponent.windowState,
                    game.videoComponent.settings);
                }
            default: {
            }
        }
    };

#pragma endregion

#pragma region window loop
    while (window.isOpen()) {
        game.dt = game.clock.restart().asSeconds(); // seconds since last frame

        window.handleEvents(onClose, onKeyPressed);

        // Update data
        world.update(game.dt);
        background.loop(game.videoComponent.camera);
        ground.loop(game.videoComponent.camera);

        // Camera
        game.videoComponent.camera.follow_point(player_1.shape.getPosition());

        // Update the view to follow player
        window.setView(game.videoComponent.camera.view);

        // Clear and draw
        window.clear();
        world.draw(window);
        window.display();
    }
#pragma endregion
}