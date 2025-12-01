#include <SFML/Graphics.hpp>
#include "../Includes/Game.hpp"
#include "../Includes/World.hpp"
#include "../Includes/Player.hpp"
#include "../Includes/Background.hpp"
#include "../Includes/Ground.hpp"


int main() {
#pragma region game settup
    const auto* title = "Bonk Game";
    Game game(title);

    // Reference the window
    sf::RenderWindow &window = game.video.window;
#pragma endregion

#pragma region background
    sf::Texture backgroundTexture(RESOURCES_PATH "Custom/background.jpg");
    Background background(backgroundTexture, {window.getSize().x*3,window.getSize().y});
    sf::Texture groundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_center.png");
    sf::Texture topGroundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_top.png");
    const float groundLevel = static_cast<float>(window.getSize().y) - static_cast<float>(window.getSize().y)/5.f;
    Ground ground(groundTexture, topGroundTexture, {window.getSize().x*3, window.getSize().y}, groundLevel);
#pragma endregion

#pragma region player
    auto playerTexture(sf::Texture(RESOURCES_PATH "Custom/AnimationSheet_Character.png"));
    Player player1(playerTexture, {
        sf::Keyboard::Scancode::A,
        sf::Keyboard::Scancode::D,
        sf::Keyboard::Scancode::W,
        sf::Keyboard::Scancode::LShift,
        sf::Keyboard::Scancode::F
    });
    player1.setGroundLevel(groundLevel);
    player1.setPosition({background.shape.getSize().x-background.shape.getSize().x/3.f,
        player1.physics.GROUND_LEVEL-player1.size.y});

    game.video.camera.pTarget = &player1;

    Player player2(playerTexture, {
        sf::Keyboard::Scancode::Left,
        sf::Keyboard::Scancode::Right,
        sf::Keyboard::Scancode::Up,
        sf::Keyboard::Scancode::RShift,
        sf::Keyboard::Scancode::Numpad0
    });
    player2.shape.setFillColor(sf::Color({10,100,250}));
    player2.setGroundLevel(groundLevel);
    player2.setPosition({background.shape.getSize().x-background.shape.getSize().x/6.f,
        player2.physics.GROUND_LEVEL-player2.size.y});

#pragma endregion

#pragma region world
    World world{};
    world.add(background);
    world.add(ground);
    world.add(player2);
    world.add(player1);
    world.pGame = &game;
    game.pWorld = &world;
#pragma endregion

#pragma region window loop
    while (window.isOpen()) {
        game.update();
    }
#pragma endregion
}