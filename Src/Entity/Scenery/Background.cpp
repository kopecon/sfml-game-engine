//
// Created by Andrew on 13/11/2025.
//

#include "../../../Includes/Entity/Scenery/Background.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


namespace scenery {

#pragma region constructors
    Background::Background(World &world, const entityID ID) :
        Scenery(world, ID)
        {
            buildRender();
        }

    Background::Background(World &world, const entityID ID, std::string name) :
        Scenery(world, ID, std::move(name))
        {
            buildRender();
        }

    std::string Background::getClassName() const {
        return "Background";
    }
#pragma endregion

    void Background::buildRender() {
        auto &texture = game.textures.background;

        texture.setRepeated(true);

        auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(texture.getSize()));

        shape->setTexture(&texture);

        auto composite = std::make_unique<Composite>();
        composite->addShape(std::move(shape));
        render.addComposite(std::move(composite));
        render.setOrigin(render.getCenter());
    }
}