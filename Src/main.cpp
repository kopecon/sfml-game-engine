#include <SFML/Graphics.hpp>
#include "../Includes/Game/Game.hpp"
#include "../Includes/World/World.hpp"
#include "../Includes/Entity/Player/Player.hpp"
#include "../Includes/Entity/Scenery/Background.hpp"
#include "../Includes/Entity/Scenery/Ground.hpp"


int main() {
    #pragma region game settup
    Game game("Bonk Game");
    const sf::RenderWindow &window = game.getVideo().getWindow();  // Reference the game window
    #pragma endregion

    #pragma region world
    auto &worldForest = game.createWorld("Forest");
    #pragma endregion

    #pragma region background
    (void) worldForest.createEntity<scenery::Background>();
    (void) worldForest.createEntityAt<scenery::Ground>({0.f, worldForest.groundLevel});
    #pragma endregion

    #pragma region player
    Controls p1controls;
    p1controls.left        = sf::Keyboard::Scancode::A     ;
    p1controls.right       = sf::Keyboard::Scancode::D     ;
    p1controls.jump        = sf::Keyboard::Scancode::W     ;
    p1controls.run         = sf::Keyboard::Scancode::LShift;
    p1controls.attack      = sf::Keyboard::Scancode::F     ;
    p1controls.crouch      = sf::Keyboard::Scancode::S     ;
    p1controls.concentrate = sf::Keyboard::Scancode::C     ;

    Controls p2controls;
    p2controls.left        = sf::Keyboard::Scancode::Left   ;
    p2controls.right       = sf::Keyboard::Scancode::Right  ;
    p2controls.jump        = sf::Keyboard::Scancode::Up     ;
    p2controls.run         = sf::Keyboard::Scancode::RShift ;
    p2controls.attack      = sf::Keyboard::Scancode::Numpad0;

    auto &player1 = worldForest.createEntityAt<player::Player>({-0.f, 10.f}, p1controls);
    auto &player2 = worldForest.createEntityAt<player::Player>({ 100.f, 10.f}, p2controls);
    game.getVideo().getCamera().pTarget = &player1;
    player2.render.setColor(sf::Color({0,200,255}));
    worldForest.remove(player2);
    #pragma endregion

    #pragma region window loop
    while (window.isOpen()) {
        game.update();
    }
    #pragma endregion
}