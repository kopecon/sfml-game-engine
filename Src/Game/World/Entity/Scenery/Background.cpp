#include "Game/World/Entity/Scenery/Background.hpp"
#include "Game/Game.hpp"
#include "Game/Engines/SceneGraph/Sprite.hpp"
#include "Game/World/World.hpp"


namespace scenery {

#pragma region constructors
    Background::Background(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name)) {
            buildRender();
        }

    std::string Background::getClassName() {
        return "Background";
    }
#pragma endregion

    void Background::buildRender() {
        auto &texture = game.getTextures().background;
        auto sprite = std::make_unique<Sprite>(texture);
        sprite->rename("background");
        const auto spriteSize = sprite->getGlobalBounds().size;
        // Fit sprite to window
        sprite->setScale(
            hd::divide(game.getVideo().getWindowSize(), spriteSize)
        );
        // Make 3 "copies"
        sprite->getSprite().setTextureRect(
            sf::IntRect({0, 0},
                sf::Vector2i(
                    static_cast<int>(spriteSize.x)*3,
                    static_cast<int>(spriteSize.y)
                )
            )
        );
        render_.add(std::move(sprite));
        render_.setOrigin(render_.getCenter());
    }

    void Background::update() {
        render_.loop();
    }
}
