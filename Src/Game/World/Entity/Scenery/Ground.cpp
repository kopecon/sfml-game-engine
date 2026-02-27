#include "Game/World//Entity/Scenery/Ground.hpp"
#include "Game/Game.hpp"
#include "Game/Engines/SceneGraph/ParallaxLayer.hpp"
#include "Game/Engines/SceneGraph/Sprite.hpp"
#include "Game/World/World.hpp"


namespace scenery {
#pragma region constructors
    Ground::Ground(World &world, const entityID ID, std::string name) : Entity(world, ID, std::move(name)) {
        buildRender();
    }

    std::string Ground::getClassName() {
        return "Ground";
    }
#pragma endregion

    void Ground::buildRender() {
        auto &topTex = game.getTextures().topGround;
        auto &bottomTex = game.getTextures().bottomGround;

        auto top = std::make_unique<Sprite>(topTex);
        auto bottom = std::make_unique<Sprite>(bottomTex);

        top->rename("top");
        bottom->rename("bottom");

        auto size = static_cast<float>(VideoComponent::GAME_RESOLUTION.y) / 4;
        top->setSize({size, size});
        bottom->setSize({size, size});

        top->repeat({VideoComponent::GAME_RESOLUTION.x / static_cast<int>(size) * 3, 1});
        bottom->repeat({VideoComponent::GAME_RESOLUTION.x / static_cast<int>(size) * 3, 1});

        bottom->move({top->getPosition().x, top->getPosition().y + top->getGlobalBounds().size.y});

        render_.add(std::move(top));
        render_.add(std::move(bottom));
        render_.setColor(color);
        render_.setOrigin({render_.getCenter().x, 0});
        // render_.visible = false;
    }

    void Ground::loop() const {
        for (auto *layer: layers_) {
            layer->update();
        }
    }

    void Ground::update() {
        render_.loop();
        loop();
    }
}
