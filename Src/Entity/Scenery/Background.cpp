//
// Created by Andrew on 13/11/2025.
//

#include "../../../Includes/Entity/Scenery/Background.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


namespace scenery {

#pragma region constructors
    Background::Background(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name))
        {
            buildRender();
        }

    std::string Background::getClassName() {
        return "Background";
    }
#pragma endregion

    void Background::buildRender() {
        auto &texture = game.textures.background;
        texture.setRepeated(true);

        auto sprite = std::make_unique<sf::Sprite>(texture);
        const auto spriteSize = sprite->getGlobalBounds().size;

        // Fit sprite to window
        sprite->setScale(
            hd::divide(game.video.getWindowSize(), spriteSize)
        );
        // Make 3 "copies"
        sprite->setTextureRect(
            sf::IntRect({0, 0},
                sf::Vector2i(
                    static_cast<int>(spriteSize.x)*3,
                    static_cast<int>(spriteSize.y)
                )
            )
        );
        render.root.setSprite(std::move(sprite));
        render.root.setOrigin(render.root.getCenter());
    }

    void Background::update() {
        render.loop();
    }
}
