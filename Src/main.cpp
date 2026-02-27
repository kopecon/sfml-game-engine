#include <SFML/Graphics.hpp>
#include "Game/Game.hpp"
#include "Game/World/World.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"
#include "Game/World/Entity/Actor/Player/Components/Render/PlayerSprite.hpp"
#include "Game/World/Entity/Scenery/Background.hpp"
#include "Game/World/Entity/Scenery/Ground.hpp"


int main() {
    #pragma region game settup
    Game game("Bonk Game");
    const sf::RenderWindow &window = game.getVideo().getWindow();  // Reference the game window
    #pragma endregion

    #pragma region world
    auto &worldForest = game.createWorld("Forest");
    #pragma endregion

    #pragma region background
    // (void) worldForest.createEntityAt<scenery::Background>({VideoComponent::BASE_CENTER.x, worldForest.groundLevel});
    (void) worldForest.createEntity<scenery::Background>();
    (void) worldForest.createEntityAt<scenery::Ground>({VideoComponent::BASE_CENTER.x, worldForest.groundLevel});
    #pragma endregion

    #pragma region player

    auto &player1 = worldForest.createEntityAt<player::Player>({-0.f, 10.f});
    auto &player2 = worldForest.createEntityAt<player::Player>({ 100.f, 10.f});
    player2.bindings().bind(InputSlot::S1, sf::Keyboard::Scancode::Up);
    player2.bindings().bind(InputSlot::S2, sf::Keyboard::Scancode::Left);
    player2.bindings().bind(InputSlot::S3, sf::Keyboard::Scancode::Down);
    player2.bindings().bind(InputSlot::S4, sf::Keyboard::Scancode::Right);
    player2.bindings().bind(InputSlot::S5, sf::Keyboard::Scancode::RShift);
    player2.bindings().bind(InputSlot::S6, sf::Keyboard::Scancode::Numpad0);
    player2.bindings().bind(InputSlot::S7, sf::Keyboard::Scancode::Numpad1);
    game.getVideo().getCamera().pTarget = &player1;
    player2.getRenderManager().getMainSprite().setColor(sf::Color({0,200,255}));
    // worldForest.remove(player1);
    worldForest.remove(player2);
    #pragma endregion

    // game.getAudio().music.play();

    #pragma region window loop
    while (window.isOpen()) {
        game.update();
    }
    #pragma endregion
}