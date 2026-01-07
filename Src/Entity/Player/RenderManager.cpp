//
// Created by Andrew on 02/01/2026.
//

#include "../../../Includes/Entity/Player/RenderManager.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"


namespace player {
    RenderManager::RenderManager(Player &player): player(player) {
        const auto &texture = player.game.textures.player;

        auto shape = std::make_unique<sf::RectangleShape>();
        shape->setSize(player.getCharacterSize());
        const auto shapeCenter = shape->getGeometricCenter();

        shape->setTexture(&texture);
        shape->setTextureRect(sf::IntRect({0, 0}, {32, 32}));  //32 is defined by the texture used

        auto test_shape = std::make_unique<sf::CircleShape>(10.f);
        test_shape->setOrigin(test_shape->getGeometricCenter());
        test_shape->setPosition(shapeCenter);
        test_shape->setFillColor(sf::Color(255, 255, 0));

        auto composite = std::make_unique<Composite>();
        composite->addShape(std::move(shape));
        // composite->addShape(std::move(test_shape));

        player.render.addComposite(std::move(composite));
        player.render.setOrigin(player.render.getCenter());
        // player.render.showBoundary(sf::Color::Blue);
    }
} // player