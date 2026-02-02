//
// Created by Andrew on 27/11/2025.
//

#include "../../../Includes/Entity/Scenery/Ground.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Game/Engines/SceneGraph/Sprite.hpp"
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
        auto &topTex = game.getTextures().topGround;
        auto &bottomTex = game.getTextures().bottomGround;

        topTex.setRepeated(true);
        bottomTex.setRepeated(true);

        auto top = std::make_unique<Sprite>(topTex);
        top->rename("top");
        auto bottom = std::make_unique<Sprite>(bottomTex);
        bottom->rename("bottom");
        // Stretch to window size * 3 and repeat texture.
        top->getSprite().setTextureRect(
            sf::IntRect({0, 0},
                sf::Vector2i(
                    static_cast<int>(game.getVideo().getWindowSize().x)*3,
                    static_cast<int>(top->getGlobalBounds().size.y)
                )
            )
        );
        bottom->getSprite().setTextureRect(
            sf::IntRect({0, 0},
                sf::Vector2i(
                    static_cast<int>(game.getVideo().getWindowSize().x)*3,
                    static_cast<int>(bottom->getGlobalBounds().size.y)
                )
            )
        );

        bottom->move({top->getPosition().x, top->getPosition().y + top->getGlobalBounds().size.y});

        render.add(std::move(top));
        render.add(std::move(bottom));
        render.setColor(color);
        render.setOrigin({render.getCenter().x, 0});
    }

    void Ground::update() {
        render.loop();
    }
}
