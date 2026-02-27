#include "Game/World/Entity/Scenery/Background.hpp"
#include "Game/Game.hpp"
#include "Game/Engines/SceneGraph/ParallaxLayer.hpp"
#include "Game/Engines/SceneGraph/Sprite.hpp"
#include "Game/World/World.hpp"


namespace scenery {
#pragma region constructors
    Background::Background(World &world, const entityID ID, std::string name)
        : Entity(world, ID, std::move(name)) {
        buildRender();
    }

    std::string Background::getClassName() {
        return "Background";
    }
#pragma endregion

    void Background::buildRender() {
        auto &texture = game.getTextures().background;
        auto sprite = std::make_unique<ParallaxLayer>(texture, game.getVideo().getCamera(), 1.f);
        sprite->rename("background");

        // Fit sprite to window
        constexpr auto worldSize = VideoComponent::GAME_RESOLUTION;

        const sf::Vector2u texSize = sprite->getSprite().getTexture().getSize();

        const auto scale = hd::divide(worldSize, texSize);

        sprite->setScale(scale);

        layers_.push_back(sprite.get());
        render_.add(std::move(sprite));
        // render_.visible = false;
    }

    void Background::loop() const {
        for (auto *layer: layers_) {
            layer->update();
        }
    }

    void Background::update() {
        loop();
    }
}
