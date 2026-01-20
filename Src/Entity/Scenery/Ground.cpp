//
// Created by Andrew on 27/11/2025.
//

#include "../../../Includes/Entity/Scenery/Ground.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


namespace scenery {

#pragma region constructors
    Ground::Ground(World &world, const entityID ID, std::string name) :
        Entity(world, ID, std::move(name))
        {
            buildRender();
        }

    std::string Ground::getClassName() {
        return "Ground";
    }
#pragma endregion

    void Ground::buildRender() {
        auto &topTex = game.textures.topGround;
        auto &bottomTex = game.textures.bottomGround;

        topTex.setRepeated(true);
        bottomTex.setRepeated(true);

        auto top = std::make_unique<sf::Sprite>(topTex);
        auto bottom = std::make_unique<sf::Sprite>(bottomTex);

        bottom->move({top->getPosition().x, top->getPosition().y + top->getGlobalBounds().size.y});

        auto composite = std::make_unique<Composite>(static_cast<std::string>(render.root.getName()) + "_composite");
        composite->add(std::move(top), "top");
        composite->add(std::move(bottom), "bottom");

        for (const auto &pSprite : composite->getAllSprites()) {

            const auto spriteSize = pSprite->getGlobalBounds().size;

            // Make 3 "copies"
            pSprite->setTextureRect(
                sf::IntRect({0, 0},
                    sf::Vector2i(
                        static_cast<int>(game.video.getWindowSize().x)*3,
                        static_cast<int>(spriteSize.y)
                    )
                )
            );
        }

        render.root.add(std::move(composite));
        render.root.setColor(color);
        render.root.setOrigin({render.root.getCenter().x, 0});
        // render.showBoundary();
    }

    void Ground::update() {
        render.loop();
    }
}
