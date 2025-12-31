//
// Created by Andrew on 13/11/2025.
//

#include "../../../Includes/Entity/Scenery/Background.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"

#include <iostream>


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

    std::string Background::className() const {
        return "Background";
    }
#pragma endregion

    sf::Texture * Background::getTexture() {
        return &game.textures.background;
    }

    void Background::buildRender() {
        auto &texture = game.textures.background;

        texture.setRepeated(true);

        auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(texture.getSize()));

        shape->setTexture(&texture);

        render.repeatToWidth(shape.get());

        shape->setOrigin(shape->getGeometricCenter());

        render.addShape(std::move(shape));
    }

    void Background::init() {
        Scenery::init();
        shape.setScale({stretchFactor, 1});
        shape.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(shape.getGlobalBounds().size)));
        const sf::Vector2f sizeRatio = getWindowToShapeSizeRatio();
        shape.setScale({shape.getScale().x * sizeRatio.x * stretchFactor, shape.getScale().y * sizeRatio.y});
    }


}