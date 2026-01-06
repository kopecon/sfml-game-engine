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

    std::string Ground::getClassName() const {
        return "Ground";
    }
#pragma endregion

    void Ground::buildRender() {
        auto &topTex = game.textures.topGround;
        auto &bottomTex = game.textures.bottomGround;

        topTex.setRepeated(true);
        bottomTex.setRepeated(true);

        auto top = std::make_unique<sf::RectangleShape>(sf::Vector2f(topTex.getSize()));
        auto bottom = std::make_unique<sf::RectangleShape>(sf::Vector2f(bottomTex.getSize()));

        top->setTexture(&topTex);
        bottom->setTexture(&bottomTex);

        bottom->move({top->getPosition().x, top->getPosition().y + top->getSize().y});

        const auto topCenter = top->getGeometricCenter();

        auto composite = std::make_unique<Composite>();
        composite->addShape(std::move(top));
        composite->addShape(std::move(bottom));
        composite->setOrigin({topCenter.x, 0});
        render.addComposite(std::move(composite));
        render.setFillColor(color);
        render.setOrigin({render.getGeometricalCenter().x, 0});
        // render.showBoundary();
    }
}