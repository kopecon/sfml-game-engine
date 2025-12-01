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

#pragma region textures
    sf::Texture backgroundTexture(RESOURCES_PATH "Custom/background.jpg");
    sf::Texture groundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_center.png");
    sf::Texture topGroundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_top.png");
#pragma endregion

#pragma region background
    Background background(backgroundTexture, window.getSize());
    Ground ground(groundTexture, topGroundTexture, window.getSize());
#pragma endregion

#pragma region player
    auto playerTexture(sf::Texture(RESOURCES_PATH "Custom/AnimationSheet_Character.png"));
    Player player1(playerTexture, {
        sf::Keyboard::Scancode::A,
        sf::Keyboard::Scancode::D,
        sf::Keyboard::Scancode::W,
        sf::Keyboard::Scancode::LShift,
        sf::Keyboard::Scancode::F});

    Player player2(playerTexture, {
        sf::Keyboard::Scancode::Left,
        sf::Keyboard::Scancode::Right,
        sf::Keyboard::Scancode::Up,
        sf::Keyboard::Scancode::RShift,
        sf::Keyboard::Scancode::Numpad0});

    player2.shape.setFillColor(sf::Color({10,100,250}));

    player1.moveShape({-static_cast<float>(window.getSize().x)/10.f, 0});
    player2.moveShape({ static_cast<float>(window.getSize().x)/10.f, 0});

#pragma endregion

#pragma region world
    World world{};
    world.add(background);
    world.add(ground);
    world.add(player2);
    world.add(player1);
    world.pGame = &game;
    game.pWorld = &world;
    world.groundLevel = window.getSize().y/4.f;
    ground.setGroundLevel();
#pragma endregion

#pragma region window loop
    game.video.camera.pTarget = &player1;

    while (window.isOpen()) {
        game.update();
    }
#pragma endregion
}