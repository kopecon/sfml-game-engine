#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Includes/Game/Game.hpp"
#include "../Includes/World/World.hpp"
#include "../Includes/Entity/Player.hpp"
#include "../Includes/Scenery/Background.hpp"
#include "../Includes/Scenery/Ground.hpp"


int main() {
#pragma region game settup
    Game game("Bonk Game");
    const sf::RenderWindow &window = game.video.window;  // Reference the game window
#pragma endregion

#pragma region textures
    sf::Texture backgroundTexture(RESOURCES_PATH "Custom/background.jpg");
    sf::Texture bodyGroundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_center.png");
    sf::Texture topGroundTexture(RESOURCES_PATH "kenney_new-platformer-pack-1.0/Sprites/Tiles/Double/terrain_dirt_block_top.png");
    sf::Texture playerTexture(sf::Texture(RESOURCES_PATH "Custom/AnimationSheet_Character.png"));
#pragma endregion

#pragma region world
    const auto worldForest = game.createWorld("Forest");
    // (void) worldForest->createEntity<Background>("Forest", window.getSize(), backgroundTexture);

    Controls p1controls;
    p1controls.left   = sf::Keyboard::Scancode::A;
    p1controls.right  = sf::Keyboard::Scancode::D;
    p1controls.jump   = sf::Keyboard::Scancode::W;
    p1controls.run    = sf::Keyboard::Scancode::LShift;
    p1controls.attack = sf::Keyboard::Scancode::F;

    Controls p2controls;
    p2controls.left   = sf::Keyboard::Scancode::Left;
    p2controls.right  = sf::Keyboard::Scancode::Right;
    p2controls.jump   = sf::Keyboard::Scancode::Up;
    p2controls.run    = sf::Keyboard::Scancode::RShift;
    p2controls.attack = sf::Keyboard::Scancode::Numpad0;

    worldForest->createEntity<Player>("player1", p1controls, playerTexture);
    // worldForest->createEntity<Player>("player2", p2controls, playerTexture);

    // game.video.camera.pTarget = forest->findEntities<Player>()[0];
#pragma endregion

#pragma region background
#pragma endregion

#pragma region player
#pragma endregion

#pragma region window loop
    // game.video.camera.pTarget = &player1;

    while (window.isOpen()) {
        game.update();
    }
#pragma endregion
}