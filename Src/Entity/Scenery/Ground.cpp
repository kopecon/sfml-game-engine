//
// Created by Andrew on 27/11/2025.
//

#include "../../../Includes/Entity/Scenery/Ground.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


namespace scenery {

#pragma region constructors
    Ground::Ground(World &world, const entityID ID) :
        Scenery(world, ID)
        {
            buildRender();
        }

    Ground::Ground(World &world, const entityID ID, std::string name) :
        Scenery(world, ID, std::move(name))
        {
            buildRender();
        }

    std::string Ground::className() const {
        return "Ground";
    }
#pragma endregion

    sf::Texture * Ground::getTexture() {
        return &game.textures.topGround;
    }

    void Ground::buildRender() {
        auto &topTex = game.textures.topGround;
        auto &bottomTex = game.textures.bottomGround;

        topTex.setRepeated(true);
        bottomTex.setRepeated(true);

        auto top = std::make_unique<sf::RectangleShape>(sf::Vector2f(topTex.getSize()));
        auto bottom = std::make_unique<sf::RectangleShape>(sf::Vector2f(bottomTex.getSize()));

        top->setTexture(&topTex);
        bottom->setTexture(&bottomTex);

        render.repeatToWidth(top.get());
        render.repeatToWidth(bottom.get());

        top->setOrigin(top->getGeometricCenter());
        bottom->setOrigin(bottom->getGeometricCenter());

        bottom->move({top->getPosition().x, top->getPosition().y + top->getSize().y});

        render.addShape(std::move(top));
        render.addShape(std::move(bottom));
        render.setFillColor(color);
    }
}
